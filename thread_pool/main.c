#include "factory.h"

int main(int argc,char* argv[]){
    ARGS_CHECK(argc,5);
    factory_t fac;
    int thread_num=atoi(argv[3]),capacity=atoi(argv[4]);
    factory_init(&fac,thread_num,capacity);
    factory_start(&fac,thread_num);
    pque_t pque=&fac.que;
    int serfd,cfd;
    tcp_init(&serfd,argv[1],argv[2]);
    struct sockaddr_in client_addr;
    socklen_t addrlen=sizeof(client_addr);
    int epfd=epoll_create(1);
    struct epoll_event eve[1];
    epoll_add(epfd,serfd);
    int ready_num,i;
    pnode_t pcur;
    while(1){
        ready_num=epoll_wait(epfd,eve,1,-1);
        for(i=0;i<1;i++){
            if(eve[i].data.fd==serfd){//有客户端发起任务，连接后，任务挂入队列
                bzero(&client_addr,sizeof(client_addr));
                cfd=accept(serfd,(struct sockaddr*)&client_addr,&addrlen);
                ERROR_CHECK(cfd,-1,"accept");
                printf("client ip:%s port:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
                pcur=(pnode_t)malloc(sizeof(node_t));
                bzero(pcur,sizeof(node_t));
                pcur->cfd=cfd;
                pthread_mutex_lock(&pque->mutex);//互斥修改队列
                inque(pque,pcur);
                pthread_mutex_unlock(&pque->mutex);
                pthread_cond_signal(&fac.cond);//唤醒等待线程
            }
        }
    }
    return 0;
}