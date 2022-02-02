#include <func.h>

int main(int argc,char* argv[]){
    ARGS_CHECK(argc,3);
    int serfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in ser_addr;
    bzero(&ser_addr,sizeof(ser_addr));
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_port=htons(atoi(argv[2]));
    ser_addr.sin_addr.s_addr=inet_addr(argv[1]);
    socklen_t addrlen=sizeof(ser_addr);
    int ret=connect(serfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
    ERROR_CHECK(ret,-1,"connnect");
    char buf[128]={0};
    int epfd=epoll_create(1);
    struct epoll_event event,eve[2];
    event.data.fd=STDIN_FILENO;
    event.events=EPOLLIN;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=serfd;
    event.events=EPOLLIN;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,serfd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int ready_num,i;
    while(1){
        ready_num=epoll_wait(epfd,eve,2,-1);
        for(i=0;i<ready_num;i++){
            if(eve[i].data.fd==STDIN_FILENO){
                bzero(buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                if(!ret){
                    printf("I want to go!\n");
                    return 0;
                }else{
                    send(serfd,buf,strlen(buf)-1,0);
                }
            }
            if(eve[i].data.fd==serfd){
                bzero(buf,sizeof(buf));
                ret=recv(serfd,buf,sizeof(buf),0);
                ERROR_CHECK(ret,-1,"recv");
                if(!ret){
                    printf("byebye!\n");
                    return 0;
                }else{
                    puts(buf);
                }
            }
        }
    }
    close(serfd);
    return 0;
}