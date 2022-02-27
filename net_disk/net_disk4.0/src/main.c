#include "factory.h"
int exit_fds[2];
void exit_func(int signum){
    write(exit_fds[1],&signum,1);
}

int main(){
    char ip[16]={0};
	char port[10]={0};
    int ret=init_arg(ip,port);
    if(!ret){
        printf("error conf!\n");
    }
    pipe(exit_fds);
    if(fork()){//父进程协助退出
        close(exit_fds[0]);
        signal(SIGUSR1,exit_func);
        wait(NULL);
        return 0;
    }
    close(exit_fds[1]);

    factory_t fac;
    int thread_num=THREAD_NUM,capacity=CAPACITY;
    factory_init(&fac,thread_num,capacity);
    factory_start(&fac,thread_num);

    int serfd,cfd,curfd;
    tcp_init(&serfd,ip,port);
    struct sockaddr_in client_addr;
    socklen_t addrlen=sizeof(client_addr);
    int epfd=epoll_create(1);
    fac.epfd=epfd;
    struct epoll_event* eve=(struct epoll_event*)calloc(capacity+2,sizeof(struct epoll_event));
    epoll_add(epfd,serfd);
    epoll_add(epfd,exit_fds[0]);
    int ready_num,i,j;
    
    client_state* c_state=(client_state*)calloc(capacity,sizeof(client_state));
    bzero(c_state,capacity*sizeof(client_state));
    cmd_train cur_cmd;
    pwd_t pt;
    int datalen;
    char flag,id[20];
    
    while(1){//主线程负责客户端连接登陆，服务器端的退出
        ready_num=epoll_wait(epfd,eve,capacity+2,-1);
        for(i=0;i<ready_num;i++){
            //有客户端发起连接,接收用户名密码,执行登录业务
            if(eve[i].data.fd==serfd){
                bzero(&client_addr,sizeof(client_addr));
                bzero(id,sizeof(id));
                bzero(&pt,sizeof(pwd_t));
                cfd=accept(serfd,(struct sockaddr*)&client_addr,&addrlen);
                ERROR_CHECK(cfd,-1,"accept");
                
                recv_cmd(&cur_cmd,cfd);//接用户名
                strcpy(pt.usr_name,cur_cmd.buf);
                if(LOGIN==cur_cmd.cmd_type){//登陆命令发送盐值
                    usrinfo_seek(cur_cmd.buf,2,pt.salt);//查盐值
                    ret=pwd_check(&pt,cfd);
                    if(ret){//登陆成功，epoll监控,并维护客户端状态
                        epoll_add(epfd,cfd);
                        for(j=0;c_state[j].cfd;j++);
                        c_state[j].cfd=cfd;
                        usrinfo_seek(pt.usr_name,0,id);
                        c_state[j].id=atoi(id);
                        c_state[j].path[0]='/';
                        strcpy(c_state[j].path+1,pt.usr_name);
                        flag=1;
                        send(cfd,&flag,1,0);
                        printf("client ip:%s port:%d connect\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
                    }else{
                        flag=0;
                        send(cfd,&flag,1,0);
                        close(cfd);
                    }
                }
                else if(REGISTER==cur_cmd.cmd_type){//用户注册,接用户名发送盐值
                    usr_register(&pt,cfd);
                    epoll_add(epfd,cfd);
                    for(j=0;c_state[j].cfd;j++);
                    c_state[j].cfd=cfd;
                    usrinfo_seek(pt.usr_name,0,id);
                    c_state[j].id=atoi(id);
                    c_state[j].path[0]='/';
                    strcpy(c_state[j].path+1,pt.usr_name);
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
                curfd=eve[i].data.fd;
                recv_cmd(&cur_cmd,curfd);
                for(j=0;c_state[j].cfd!=curfd;j++);//获取当前处理客户端状态
                if(LS==cur_cmd.cmd_type){
                    ls_func(c_state[j]);
                }else if(CD==cur_cmd.cmd_type){
                    cd_func(cur_cmd,&c_state[j]);
                }else if(PWD==cur_cmd.cmd_type){
                    pwd_func(c_state[j]);
                }else if(MKDIR==cur_cmd.cmd_type){
                    mkdir_func(cur_cmd,c_state[j]);
                }else if(REMOVE==cur_cmd.cmd_type){

                }else if(GETS==cur_cmd.cmd_type){
                    mission_inque(epfd,c_state+j,&fac);
                }else if(PUTS==cur_cmd.cmd_type){
                    mission_inque(epfd,c_state+j,&fac);
                }
                
            }
        }
    }
    return 0;
}