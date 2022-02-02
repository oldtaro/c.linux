#include <func.h>
//即时聊天服务器端,可以重连
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
    char buf[128]={0};
    fd_set readset,tempset;//readset服务器自身读集初始状态,用tempset来存工作检测集
    FD_ZERO(&readset);
    FD_SET(serfd,&readset);//用于检测是否有客户端连接
    FD_SET(STDIN_FILENO,&readset);
    while(1){
        memcpy(&tempset,&readset,sizeof(fd_set));
        ret=select(1024,&tempset,NULL,NULL,NULL);
        ERROR_CHECK(ret,-1,"select");
        if(FD_ISSET(serfd,&tempset)){//客户端发起连接
            //4.接受客户机套接字,accept调用完成3次握手
            cfd=accept(serfd,(struct sockaddr*)&client_addr,&addr_len);//(serfd,结构体指针同bind,结构体长(指针类型))
            //cfd有输入输出缓冲区,通过cfd与客户机通信
            ERROR_CHECK(cfd,-1,"accept");
            FD_SET(cfd,&readset);//客户端套接口描述符入默认检测读集
            printf("client ip=%s,client port=%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
        }
        if(FD_ISSET(STDIN_FILENO,&tempset)){//标准输入可读,向客户机发送
            bzero(buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(!ret){//服务器端退出
                printf("I want to go!\n");
                break;
            }else{
                send(cfd,buf,strlen(buf)-1,0);//发送至客户端,*不带\n
            }
        }
        if(FD_ISSET(cfd,&tempset)){//客户端有发送数据
            bzero(buf,sizeof(buf));
            ret=recv(cfd,buf,sizeof(buf),0);
            if(!ret){//客户端断开
                printf("byebye!\n");
                FD_CLR(cfd,&readset);//删除默认检测读集中的客户端套接口描述符
            }else{
                puts(buf);
            }
        }
    }
    close(cfd);
    close(serfd);
    return 0;
}