#include "factory.h"
int exit_fds[2];
void exit_func(int signum){
    write(exit_fds[1],&signum,1);
}

int main(int argc,char* argv[]){
    ARGS_CHECK(argc,5);
    pipe(exit_fds);
    if(fork()){//父进程协助退出
        close(exit_fds[0]);
        signal(SIGUSR1,exit_func);
        wait(NULL);
        return 0;
    }
    close(exit_fds[1]);

    factory_t fac;
    int thread_num=atoi(argv[3]),capacity=atoi(argv[4]);
    factory_init(&fac,thread_num,capacity);
    factory_start(&fac,thread_num);
    pque_t pque=&fac.que;

    int serfd,cfd,curfd;
    tcp_init(&serfd,argv[1],argv[2]);
    struct sockaddr_in client_addr;
    socklen_t addrlen=sizeof(client_addr);
    int epfd=epoll_create(1);
    struct epoll_event* eve=(struct epoll_event*)calloc(capacity+2,sizeof(struct epoll_event));
    epoll_add(epfd,serfd);
    epoll_add(epfd,exit_fds[0]);
    int ready_num,i;
    pnode_t pcur;
    usr_info usr_cur;
    char salt[15],flag;
    int ret,datalen;
    
    while(1){//主线程负责客户端连接登陆，服务器端的退出
        ready_num=epoll_wait(epfd,eve,capacity+2,-1);
        for(i=0;i<ready_num;i++){
            //有客户端发起连接,接收用户名密码,执行登录业务
            if(eve[i].data.fd==serfd){
                bzero(&client_addr,sizeof(client_addr));
                cfd=accept(serfd,(struct sockaddr*)&client_addr,&addrlen);
                ERROR_CHECK(cfd,-1,"accept");
                bzero(&usr_cur,sizeof(usr_cur));
                recv(cfd,&datalen,4,0);
                recv(cfd,usr_cur.usr_name,datalen,0);//接收用户名
                recv(cfd,&datalen,4,0);
                recv(cfd,usr_cur.usr_pwd,datalen,0);//接密码

                bzero(salt,sizeof(salt));
                mysql_seek("usr_info","usr_name",usr_cur.usr_name,2,salt);//查用户信息表
                if(salt[0]){//已注册用户取得盐值
                    ret=pwd_check(usr_cur.usr_name,usr_cur.usr_pwd,salt);
                    if(ret){//登陆成功通知客户端，epoll监控
                        epoll_add(epfd,cfd);
                        flag=1;
                        send(cfd,&flag,1,0);
                        printf("client ip:%s port:%d connect\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
                    }else{
                        flag=0;
                        send(cfd,&flag,1,0);
                        close(cfd);
                    }
                }else{//未注册用户，注册
                    usr_register(usr_cur.usr_name,usr_cur.usr_pwd);
                    epoll_add(epfd,cfd);
                    flag=1;
                    send(cfd,&flag,1,0);
                    printf("client ip:%s port:%d register,connect\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
                }
            }

            else if(eve[i].data.fd==exit_fds[0]){//收到退出信号
                for(i=0;i<thread_num;i++){
                    pthread_cancel(fac.pthid[i]);
                }
                for(i=0;i<thread_num;i++){
                    pthread_join(fac.pthid[i],NULL);
                }
                exit(0);
            }
            
            else{//命令处理
                
            }
        }
    }
    return 0;
}