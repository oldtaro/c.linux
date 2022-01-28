#include <func.h>
//聊天客户机端
int main(int argc,char* argv[]){
    ARGS_CHECK(argc,3);
    int serfd;
    serfd=socket(AF_INET,SOCK_STREAM,0);//(IPv4,tcp,0)1.生成一个套接口描述符
    ERROR_CHECK(serfd,-1,"socket");
    struct sockaddr_in ser_addr;//现在常用结构体,绑定时其结构体指针应强转(struct sockaddr*),bind调用中未更改参数类型
    ser_addr.sin_family=AF_INET;//IPv4
    ser_addr.sin_port=htons(atoi(argv[2]));//端口号转换为网络字节序
    ser_addr.sin_addr.s_addr=inet_addr(argv[1]);//ip地址转换为网络字节序
    int ret=connect(serfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));//7.客户端连接服务器套接字
    ERROR_CHECK(ret,-1,"connect");
    ret=send(serfd,"hello",5,0);
    ERROR_CHECK(ret,-1,"send");
    char buf[128]={0};
    ret=recv(serfd,buf,sizeof(buf),0);
    ERROR_CHECK(ret,-1,"recv");
    printf("I am client, recieve:%s\n",buf);
    close(serfd);
    return 0;
}