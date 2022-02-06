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
    //客户端接受文件
    int data_len;
    char buf[1024]={0};
    recv(serfd,&data_len,4,0);//接收文件名长度
    recv(serfd,buf,data_len,0);//1.接收文件名，创建一个空文件
    int fd=open(buf,O_RDWR|O_CREAT,0666);
    while(1){
        recv(serfd,&data_len,4,0);//接收该段文件内容长度
        if(data_len>0){//有内容
            recv(serfd,buf,data_len,0);
            write(fd,buf,data_len);
        }else{//结尾
            break;
        }
    }
    close(fd);
    close(serfd);
    return 0;
}