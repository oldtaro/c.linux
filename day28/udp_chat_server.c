#include <func.h>
//UDP即时聊天服务器端
int main(int argc,char* argv[]){
    ARGS_CHECK(argc,3);
    int serfd=socket(AF_INET,SOCK_DGRAM,0);//1.套接口描述符,SOCK_DGRAM UDP
    ERROR_CHECK(serfd,-1,"socket");
    struct sockaddr_in ser_addr,client_addr;
    bzero(&ser_addr,sizeof(ser_addr));
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_addr.s_addr=inet_addr(argv[1]);
    ser_addr.sin_port=htons(atoi(argv[2]));
    int ret;
    ret=bind(serfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));//2.绑定
    ERROR_CHECK(ret,-1,"bind");
    bzero(&client_addr,sizeof(client_addr));
    socklen_t addrlen=sizeof(client_addr);
    char buf[128]={0};
    //3.UDP C/S通信前服务器端需先接收一次客户端数据,知道与谁通信
    ret=recvfrom(serfd,buf,sizeof(buf),0,(struct sockaddr*)&client_addr,&addrlen);
    printf("client ip=%s,port=%d\n%s\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),buf);
    ERROR_CHECK(ret,-1,"recvfrom");
    fd_set readset;
    while(1){
        FD_ZERO(&readset);
        FD_SET(serfd,&readset);
        FD_SET(STDIN_FILENO,&readset);
        ret=select(serfd+1,&readset,NULL,NULL,NULL);
        ERROR_CHECK(ret,-1,"select");
        if(FD_ISSET(STDIN_FILENO,&readset)){//标准输入有数据向客户端发送
            bzero(buf,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));
            ret=sendto(serfd,buf,strlen(buf)-1,0,(struct sockaddr*)&client_addr,sizeof(client_addr));//5.发送至客户端
            ERROR_CHECK(ret,-1,"sendto");
        }
        if(FD_ISSET(serfd,&readset)){//客户端有发送数据,则接收
            bzero(buf,sizeof(buf));
            ret=recvfrom(serfd,buf,sizeof(buf),0,(struct sockaddr*)&client_addr,&addrlen);
            ERROR_CHECK(ret,-1,"recvfrom");
            puts(buf);
        }
    }
    close(serfd);
    return 0;
}