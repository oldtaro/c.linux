#include "process_pool.h"

int mk_child(pprocess_data_t child_p,int process_num){
    int i;
    int fds[2];
    pid_t cur_pid;
    for(i=0;i<process_num;i++){
        socketpair(AF_LOCAL,SOCK_STREAM,0,fds);//全双工管道的建立
        cur_pid=fork();
        if(0==cur_pid){//子进程
            close(fds[1]);//子进程fds[0]端，父进程fds[1]端
            child_mission(fds[0]);
        }
        close(fds[0]);
        child_p[i].fd=fds[1];
        child_p[i].pid=cur_pid;
        child_p[i].busy=0;//初始为空闲
#ifdef DEBUG
    printf("child_p[%d] fd:%d,pid:%d\n",i,child_p[i].fd,child_p[i].pid);
#endif
    }
}

int child_mission(int fd){
   int cfd,ret;
   char flag=1;
   while(1){
        recv_fd(fd,&cfd);//子进程接受任务
        printf("gets task,client_fd:%d",cfd);
        trans_file(cfd);//发送文件给客户端
        close(cfd);
        write(fd,&flag,sizeof(flag));//通知父进程任务完成
   }
   return 0;
}

