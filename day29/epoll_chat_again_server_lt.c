#include <func.h>
//水平触发,可重连即时聊天服务器端
int main(int argc,char* argv[]){
    ARGS_CHECK(argc,3);
    int serfd=socket(AF_INET,SOCK_STREAM,0),cfd;
    ERROR_CHECK(serfd,-1,"socket");
    int ret,reuse=1;
    ret=setsockopt(serfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));//设置端口可重用,处于time_wait状态端口可立即重用
    struct sockaddr_in ser_addr,client_addr;
    bzero(&ser_addr,sizeof(ser_addr));
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_addr.s_addr=inet_addr(argv[1]);
    ser_addr.sin_port=htons(atoi(argv[2]));
    ret=bind(serfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
    ERROR_CHECK(ret,-1,"bind");
    ret=listen(serfd,10);
    ERROR_CHECK(ret,-1,"listen");
    socklen_t addrlen=sizeof(client_addr);
    //epoll
    int epfd=epoll_create(1);
    ERROR_CHECK(ret,-1,"epoo_create");
    struct epoll_event event,eve[2];
    event.data.fd=STDIN_FILENO;
    event.events=EPOLLIN;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=serfd;
    event.events=EPOLLIN;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,serfd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    char buf[128]={0};
    int ready_num,i;
    while(1){
        ready_num=epoll_wait(epfd,eve,2,-1);//连接与通信在不同阶段,所以maxevents只需要2
        for(i=0;i<ready_num;i++){
            if(eve[i].data.fd==serfd){//客户端发起连接
                bzero(&client_addr,sizeof(client_addr));
                cfd=accept(serfd,(struct sockaddr*)&client_addr,&addrlen);
                printf("client ip:%s, port:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
                ERROR_CHECK(cfd,-1,"accept");
                event.data.fd=cfd;
                event.events=EPOLLIN;
                ret=epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&event);
                ERROR_CHECK(ret,-1,"epoll_ctl");
            }
            if(eve[i].data.fd==STDIN_FILENO){
                bzero(buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                if(!ret){
                    printf("I want to go!\n");
                    return 0;
                }else{
                    ret=send(cfd,buf,strlen(buf)-1,0);
                    ERROR_CHECK(ret,-1,"send");
                }
            }
            if(eve[i].data.fd==cfd){
                bzero(buf,sizeof(buf));
                ret=recv(cfd,buf,sizeof(buf),0);
                if(!ret){
                    event.data.fd=cfd;
                    event.events=EPOLLIN;
                    ret=epoll_ctl(epfd,EPOLL_CTL_DEL,cfd,&event);
                    close(cfd);
                    printf("bye bye!\n");
                    break;;
                }else{
                    puts(buf);
                }
            }
        }
    }
    close(serfd);
    close(cfd);
    return 0;
}
