#include "process_pool.h"

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

