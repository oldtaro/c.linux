#include "factory.h"
//线程任务以及文件传输协议,tcp,epoll

//初始化
void factory_init(pfactory_t pf,int thread_num,int capacity){
    que_init(&pf->que,capacity);//初始化任务队列
    pthread_cond_init(&pf->cond,NULL);//初始化条件变量
    pf->pthid=(pthread_t*)calloc(thread_num,sizeof(pthread_t));//申请线程id空间
    pf->start_flag=0;//设定初始状态
}
//启动线程池
int factory_start(pfactory_t pf,int thread_num){
    if(!pf->start_flag){//未启动，启动线程池
        int i,ret;
        for(i=0;i<thread_num;i++){
            ret=pthread_create(pf->pthid+i,NULL,thread_mission,pf); 
            THREAD_ERR_CHECK(ret,"pthread_create");         
        }
        pf->start_flag=1;
    }
    return 0;
}
//子线程任务
void clean_func(void* p){
    pthread_mutex_unlock((pthread_mutex_t*)p);
}
void* thread_mission(void* pf){
    pfactory_t p=(pfactory_t)pf;
    pque_t pque=&p->que;
    pnode_t pcur=NULL;
    client_state* pcs;
    cmd_train cmd;
    char file_name[50],md5[50],flag;
    int cfd,offset,puts_fd,ret;
    off_t file_size;
    while(1){
        pthread_mutex_lock(&pque->mutex);
        //使用cleanup即使线程再wait状态下被cancel后上锁，弹出处理函数解锁
        pthread_cleanup_push(clean_func,&pque->mutex);
        if(0==pque->que_size){//任务队列空睡觉，等待唤醒    
            pthread_cond_wait(&p->cond,&pque->mutex);
        }
        //出队的两种情况：1.任务执行结束后发现任务队列不空去取任务；2.被signal的wait线程去取任务
        //2的情况下signal后还没上锁就被1情况抢先上锁取得任务，若不判空会导致被唤醒线程再去取任务出错
        deque(&p->que,&pcur);
        pthread_cleanup_pop(1);
        pcs=pcur->pcs;
        cfd=pcs->cfd;
        if(pcur){//发送发文件时也应判定，取到任务
            while(recv_cmd(&cmd,cfd),cmd.buf[0]){
                if(PUTS==cmd.cmd_type){
                    bzero(md5,sizeof(md5));
                    ret=usr_puts_file(cfd,md5,&file_size);
                    if(ret){
                        update_file_size(pcs->code,cmd.buf,file_size);
                    }else{
                        insert_new_file(pcs->code,'f',pcs->id,cmd.buf,file_size,md5);
                    }
                }else if(GETS==cmd.cmd_type){
                    bzero(md5,sizeof(md5));
                    ret=seek_file_md5(pcs->code,cmd.buf,md5);
                    if(ret){//在该级目录中存在该文件发送给客户端
                        flag=1;
                        send(cfd,&flag,1,0);
                        usr_gets_file(cfd,md5);
                    }else{//通知客户端该级目录没有该文件
                        flag=0;
                        send(cfd,&flag,1,0);
                    }
                }
            }
            free(pcur);
            pcur=NULL;
        }
        epoll_add(p->epfd,pcs->cfd);//主线程传输任务完成，重新注册epoll监控
    }
}
//客户端上传
int usr_puts_file(int cfd,char* md5,off_t* pfile_size){
    int data_len,ret,exist_flag;
    char file_name[100]={0},flag;
    //1.file_pool中文件的文件名为其md5吗，在file_info中存储其文件名
    ret=recv_total(cfd,&data_len,4,0);//接收md5码长度
    SELFFUNC_ERR_CHECK(ret,"recv_total");
    ret=recv_total(cfd,md5,data_len,0);//接收md5
    SELFFUNC_ERR_CHECK(ret,"recv_total");
    //2.接收文件大小值
    ret=recv_total(cfd,&data_len,4,0);//接收文件大小值长度
    SELFFUNC_ERR_CHECK(ret,"recv_total");
    off_t file_size,offset;
    ret=recv_total(cfd,&file_size,data_len,0);//接收文件大小值
    SELFFUNC_ERR_CHECK(ret,"recv_total");
    exist_flag=file_is_exist(md5);
    sprintf(file_name,"./file_pool/%s",md5);
    int fd=open(file_name,O_RDWR|O_CREAT,0666);
    ret=ftruncate(fd,file_size);
    ERROR_CHECK(ret,-1,"ftruncate");
    void* p=mmap(NULL,file_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    struct stat file_stat;

    if(exist_flag){//文件已经存在文件池中，秒传;未传输完成文件，断点续传
        char size[64]={0};
        file_size_inpool(md5,size);
        *pfile_size=atoi(size);

        if(file_size==*pfile_size){
            flag=0;
            send(cfd,&flag,1,0);
            index_add(md5);//更新引用计数
        }else{//未上传完全，发送偏移给客户端继续上传
            flag=1;
            send(cfd,&flag,1,0);
            send(cfd,pfile_size,8,0);
            offset=*pfile_size;
            ret=recv_total(cfd,p,file_size,offset);
            SELFFUNC_ERR_CHECK(ret,"recv_total");
            stat(file_name,&file_stat);
            *pfile_size=file_stat.st_size;
            update_size_inpool(md5,*pfile_size);
            return 1;
        }
    }else{//不存在，上传后插入新文件信息
        flag=2;
        send(cfd,&flag,1,0);
        offset=0;
        ret=recv_total(cfd,p,file_size,offset);
        SELFFUNC_ERR_CHECK(ret,"recv_total");
        ret=munmap(p,file_size);
        ERROR_CHECK(ret,-1,"munmap");
        stat(file_name,&file_stat);
        *pfile_size=file_stat.st_size;
        insert_file_pool(md5,*pfile_size);
    }
    return 0;
}

//客户端下载
int usr_gets_file(int cfd,char* md5){
    train_t t;
    int ret;
    char file_name[100]={0},flag;
    sprintf(file_name,"./file_pool/%s",md5);
    //发送文件长度
    struct stat file_stat;
    stat(file_name,&file_stat);
    t.data_len=sizeof(file_stat.st_size);
    memcpy(t.buf,&(file_stat.st_size),sizeof(file_stat.st_size));
    ret=send_total(cfd,&t,t.data_len+4,0);
    SELFFUNC_ERR_CHECK(ret,"send_total");
    
    //发送整个文件内容，mmap内存映射提高效率
    int fd=open(file_name,O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    void* p=mmap(NULL,file_stat.st_size,PROT_READ,MAP_SHARED,fd,0);
    ret=send_total(cfd,p,file_stat.st_size,0);
    SELFFUNC_ERR_CHECK(ret,"send_total");
    munmap(p,file_stat.st_size);//发送完毕解除映射
    
    return 0;

}

int send_total(int cfd,void* buf,off_t length,off_t offset){//循环发送至全部被接收
    char* pcur=(char*)buf;
    off_t s_total=offset,ret;
    while(s_total<length){
        ret=send(cfd,pcur+s_total,length-s_total,0);
        if(-1==ret){//客户端断开发送失败第一次返回-1，应及时处理
            return -1;
        }
        s_total+=ret;
    }
    return 0;
}

int recv_total(int serfd,void* buf,off_t length,off_t offset){//循环接收至全部被接收
    char* pcur=(char*)buf;
    off_t r_total=offset,ret;
    while(r_total<length){
        ret=recv(serfd,pcur+r_total,length-r_total,0);
        r_total+=ret;
    }
    return 0;
}

//初始化tcp连接
int tcp_init(int* pserfd,char* ip,char* port){
    int serfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(serfd,-1,"socket");
    int reuse=1,ret;
    ret=setsockopt(serfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));//套接口在time_wait可重用
    struct sockaddr_in ser_addr;
    bzero(&ser_addr,sizeof(ser_addr));
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_addr.s_addr=inet_addr(ip);//点分十进制转换为网络字节序
    ser_addr.sin_port=htons(atoi(port));//端口号转换为网络字节序
    ret=bind(serfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
    ERROR_CHECK(ret,-1,"bind");
    ret=listen(serfd,10);
    ERROR_CHECK(ret,-1,"listen");
    *pserfd=serfd;
    return 0;
}
//epoll
int epoll_add(int epfd, int fd){
    struct epoll_event event;
    bzero(&event,sizeof(event));
    event.data.fd=fd;
    event.events=EPOLLIN;
    int ret=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    return 0;
}

int epoll_del(int epfd,int fd){
    struct epoll_event event;
    bzero(&event,sizeof(event));
    event.data.fd=fd;
    event.events=EPOLLIN;
    int ret=epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
}
