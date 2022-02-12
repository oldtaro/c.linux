#include "factory.h"
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
void* thread_mission(void* pf){
    pfactory_t p=(pfactory_t)pf;
    pque_t pque=&p->que;
    pnode_t pcur=(pnode_t)malloc(sizeof(node_t));
    while(1){
        pcur=NULL;
        pthread_mutex_lock(&pque->mutex);
        if(0==pque->que_size){//任务队列空睡觉，等待唤醒    
            pthread_cond_wait(&p->cond,&pque->mutex);
        }
        //出队的两种情况：1.任务执行结束后发现任务队列不空去取任务；2.被signal的wait线程去取任务
        //2的情况下signal后还没上锁就被1情况抢先上锁取得任务，若不判空会导致被唤醒线程再去取任务出错
        deque(&p->que,&pcur);
        pthread_mutex_unlock(&pque->mutex);
        if(pcur){//发送发文件时也应判定，取到任务
        trans_file(pcur->cfd);
        free(pcur);
        pcur=NULL;
        }
    }
}
//文件传输协议
int trans_file(int cfd){
    train_t t;
    //1.发送文件名
    t.data_len=sizeof(FILENAME);
    strcpy(t.buf,FILENAME);
    int ret=send_total(cfd,&t,t.data_len+4);
    SELFFUNC_ERR_CHECK(ret,"send_total");
    int fd=open(FILENAME,O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    //2.发送整个文件长度
    struct stat file_stat;
    stat(FILENAME,&file_stat);
    t.data_len=sizeof(file_stat.st_size);
    memcpy(t.buf,&(file_stat.st_size),sizeof(file_stat.st_size));
    ret=send_total(cfd,&t,t.data_len+4);
    SELFFUNC_ERR_CHECK(ret,"send_total");
    //3.发送整个文件内容，mmap内存映射提高效率
    void* p=mmap(NULL,file_stat.st_size,PROT_READ,MAP_SHARED,fd,0);
    ret=send_total(cfd,p,file_stat.st_size);
    SELFFUNC_ERR_CHECK(ret,"send_total");
    munmap(p,file_stat.st_size);//发送未必解除映射
    close(cfd);
}

int send_total(int cfd,void* buf,int length){//循环发送至全部被接收
    char* pcur=(char*)buf;
    int s_total=0,ret;
    while(s_total<length){
        ret=send(cfd,pcur+s_total,length-s_total,0);
        if(-1==ret){//客户端断开发送失败第一次返回-1，应及时处理
            return -1;
        }
        s_total+=ret;
    }
    return 0;
}

int recv_total(int serfd,void* buf,int length){//循环接收至全部被接收
    char* pcur=(char*)buf;
    int r_total=0,ret;
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
    ser_addr.sin_addr.s_addr=inet_addr(ip);
    ser_addr.sin_port=htons(atoi(port));
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
