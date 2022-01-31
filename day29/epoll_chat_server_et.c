#include <func.h>

void fcntl_nonblock(int fd){//改为非阻塞
    int statu=fcntl(fd,F_GETFL);//取出文件所有权限,位权限
    statu=statu|O_NONBLOCK;//修改为非阻塞
    fcntl(fd,F_SETFL,statu);
    return;
}

int main(int argc,char* argv[]){
    ARGS_CHECK(argc,3);
    int serfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(serfd,-1,"socket");
    int reuse=1,ret;
    ret=setsockopt(serfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));//改变套接口选项需要在绑定前完成
    struct sockaddr_in ser_addr,client_addr;
    bzero(&ser_addr,sizeof(ser_addr));
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_addr.s_addr=inet_addr(argv[1]);
    ser_addr.sin_port=htons(atoi(argv[2]));
    ret=bind(serfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
    ERROR_CHECK(ret,-1,"bind");
    ret=listen(serfd,10);
    ERROR_CHECK(ret,-1,"listen");
    bzero(&client_addr,sizeof(client_addr));
    socklen_t addrlen=sizeof(client_addr);
    int cfd=accept(serfd,(struct sockaddr*)&client_addr,&addrlen);
    ERROR_CHECK(cfd,-1,"accept");
    printf("client ip:%s,port:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    //epoll
    int epfd=epoll_create(1);//创建一个epoll句柄,现在size已经无限制只要填>0的数即可表示无限
    struct epoll_event event,eve[2];
    event.data.fd=STDIN_FILENO;//注册标准输入
    event.events=EPOLLIN;//可读
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_crl");
    fcntl_nonblock(cfd);//边缘触发需要使用非阻塞套接口
    event.data.fd=cfd;//注册客户端
    event.events=EPOLLIN|EPOLLET;//可读,边缘触发
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int ready_num,i;
    char buf[6]={0};
    while(1){
        ready_num=epoll_wait(epfd,eve,2,-1);//返回就绪事件数,并传入eve
        for(i=0;i<ready_num;i++){
            if(eve[i].data.fd==STDIN_FILENO){//标准输入有数据
                bzero(buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                if(!ret){//服务器端发起结束
                    printf("I want to go!\n");
                    return 0;
                }else{
                    send(cfd,buf,strlen(buf)-1,0);
                }
            }
            if(eve[i].data.fd==cfd){//客户端有发送数据
                while(1){
                bzero(buf,sizeof(buf));
                ret=recv(cfd,buf,sizeof(buf),0);
                if(!ret){//客户端发起结束
                    printf("byebye!\n");
                    return 0;
                }else if(-1==ret){
                    printf("\n");
                    break;//数据区读空,非阻塞访问失败会返回-1,即该次所有数据读取完毕换行
                }else{
                    printf("%s",buf);
                }
              }
            }
        }
    }
    close(cfd);
    close(serfd);
    return 0;
}