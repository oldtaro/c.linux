#include <func.h>
//服务器端
int main(int argc,char* argv[]){
    ARGS_CHECK(argc,3);
    int serfd,cfd;
    serfd=socket(AF_INET,SOCK_STREAM,0);//(IPv4,tcp,0)1.生成一个套接口描述符
    ERROR_CHECK(serfd,-1,"socket");
    struct sockaddr_in ser_addr,client_addr;//现在常用结构体,绑定时其结构体指针应强转(struct sockaddr*),bind调用中未更改参数类型
    bzero(&ser_addr,sizeof(client_addr));
    ser_addr.sin_family=AF_INET;//IPv4
    ser_addr.sin_port=htons(atoi(argv[2]));//端口号转换为网络字节序
    ser_addr.sin_addr.s_addr=inet_addr(argv[1]);//ip地址转换为网络字节序
    int ret=bind(serfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));//2.绑定套接口描述符和ip,端口
    ERROR_CHECK(ret,-1,"bind");
    ret=listen(serfd,10);//3.服务端开始监听,等待客户机的连接
    ERROR_CHECK(ret,-1,"listen");
    bzero(&client_addr,sizeof(client_addr));
    socklen_t addr_len=sizeof(client_addr);
    //4.接受客户机套接字,accept调用完成3次握手
    cfd=accept(serfd,(struct sockaddr*)&client_addr,&addr_len);//(serfd,结构体指针同bind,结构体长(指针类型))
    ERROR_CHECK(cfd,-1,"accept");
    printf("client ip=%s,client port=%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    char buf[128]={0};
    ret=recv(cfd,buf,sizeof(buf),0);//5.用客户机套接字来接收其发过来的数据
    ERROR_CHECK(ret,-1,"recv");
    printf("I am server, receive:%s\n",buf);
    send(cfd,"world",5,0);//6.先客户机发送
    close(cfd);
    close(serfd);
    return 0;
}