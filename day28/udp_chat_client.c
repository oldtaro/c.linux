#include <func.h>

int main(int argc,char* argv[]){
    ARGS_CHECK(argc,3);
    int serfd=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in seraddr;
    bzero(&seraddr,sizeof(seraddr));
    seraddr.sin_family=AF_INET;
    seraddr.sin_addr.s_addr=inet_addr(argv[1]);
    seraddr.sin_port=htons(atoi(argv[2]));
    socklen_t addr_len=sizeof(seraddr);
    int ret;
    ret=sendto(serfd,"hello",5,0,(struct sockaddr*)&seraddr,sizeof(seraddr));//客户机先向服务器发送一条信息
    ERROR_CHECK(ret,-1,"sendto");
    fd_set readset;
    char buf[128]={0};
    while(1){
        FD_ZERO(&readset);
        FD_SET(STDIN_FILENO,&readset);
        FD_SET(serfd,&readset);
        ret=select(serfd+1,&readset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&readset)){
            bzero(buf,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));
            ret=sendto(serfd,buf,strlen(buf)-1,0,(struct sockaddr*)&seraddr,sizeof(seraddr));
            ERROR_CHECK(ret,-1,"sendto");
        }
        if(FD_ISSET(serfd,&readset)){
            bzero(buf,sizeof(buf));
            ret=recvfrom(serfd,buf,sizeof(buf),0,NULL,NULL);
            ERROR_CHECK(ret,-1,"recvfrom");
            puts(buf);
        }
    }
    close(serfd);
    return 0;
}