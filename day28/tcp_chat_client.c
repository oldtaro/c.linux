#include <func.h>
//即时聊天客户机端
int main(int argc,char* argv[]){
    ARGS_CHECK(argc,3);
    int serfd;
    serfd=socket(AF_INET,SOCK_STREAM,0);//(IPv4,tcp,0)1.生成一个套接口描述符
    ERROR_CHECK(serfd,-1,"socket");
    struct sockaddr_in ser_addr;//现在常用结构体,绑定时其结构体指针应强转(struct sockaddr*),bind调用中未更改参数类型
    ser_addr.sin_family=AF_INET;//IPv4
    ser_addr.sin_port=htons(atoi(argv[2]));//端口号转换为网络字节序
    ser_addr.sin_addr.s_addr=inet_addr(argv[1]);//ip地址转换为网络字节序
    int ret=connect(serfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));//7.客户端连接服务器
    //服务器accept连接请求,完成三次握手即可通信
    ERROR_CHECK(ret,-1,"connect");
    fd_set readset;
    char buf[128]={0};
    while(1){
        FD_ZERO(&readset);
        FD_SET(STDIN_FILENO,&readset);
        FD_SET(serfd,&readset);
        ret=select(serfd+1,&readset,NULL,NULL,NULL);
        ERROR_CHECK(ret,-1,"select");
        if(FD_ISSET(STDIN_FILENO,&readset)){//标准输入有数据
            bzero(buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(!ret){//客户端自己退出
                printf("I want to go!\n");
                break;
            }else{
                send(serfd,buf,strlen(buf)-1,0);
            }
        }
        if(FD_ISSET(serfd,&readset)){//服务器有发送数据
            bzero(buf,sizeof(buf));
            ret=recv(serfd,buf,sizeof(buf),0);
            if(!ret){
                printf("byebye!\n");
                break;
            }else{
                puts(buf);
            }
        }
    }
    close(serfd);
    return 0;
}