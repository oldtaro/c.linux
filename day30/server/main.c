#include "process_pool.h"

int main(int argc,char* argv[]){
    if(argc!=4){
        printf("./process_pool ip port process_num\n");
    }
    int process_num=atoi(argv[3]);
    //创建管理子进程结构体
    process_data_t* child_p=(process_data_t*)calloc(process_num,sizeof(process_data_t));
    mk_child(child_p,process_num);//子进程创建
    int serfd,cfd,epfd,i,j;
    tcp_init(&serfd,argv[1],argv[2]);
    epfd=epoll_create(1);
    int ret=epoll_add(epfd,serfd);
    SELFFUNC_ERR_CHECK(ret,"epoll_add");
    for(i=0;i<process_num;i++){
        ret=epoll_add(epfd,child_p[i].fd);
        SELFFUNC_ERR_CHECK(ret,"epoll_add");
    }
    int ready_num;
    struct epoll_event* eve=(struct epoll_event*)calloc(process_num+1,sizeof(struct epoll_event));
    struct sockaddr_in client_addr;
    socklen_t addrlen=sizeof(client_addr);
    char flag;
    while(1){
        ready_num=epoll_wait(epfd,eve,process_num+1,-1);
        for(i=0;i<ready_num;i++){
            if(eve[i].data.fd==serfd){//有客户端发起连接
                bzero(&client_addr,sizeof(client_addr));
                cfd=accept(serfd,(struct sockaddr*)&client_addr,&addrlen);
                ERROR_CHECK(cfd,-1,"accept");
                for(j=0;j<process_num;j++){//寻找空闲进程分配任务
                    if(0==child_p[j].busy){
                        send_fd(child_p[j].fd,cfd);
                        child_p[j].busy=1;//分配任务后置子进程为忙碌
                        printf("child process: %d is busy!\n",child_p[i].pid);
                        break;
                    }
                }
                close(cfd);
            }
            for(j=0;j<process_num;j++){
                if(eve[i].data.fd==child_p[j].fd){//子进程管道对端可读，表示任务完成
                    read(child_p[j].fd,&flag,sizeof(flag));//读掉管道内标识内容，不然会一直可读
                    child_p[j].busy=0;//置子进程为空闲
                    printf("child process %d is unbusy!\n",child_p[j].pid);
                    break;
                }
            }
        }
    }
    return 0;
}