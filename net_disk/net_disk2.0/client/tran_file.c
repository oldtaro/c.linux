#include "process_pool.h"

int recv_total(int serfd,void* buf,int length){//循环接收至全部被接收
    char* pcur=(char*)buf;
    int r_total=0,ret;
    while(r_total<length){
        ret=recv(serfd,pcur+r_total,length-r_total,0);
        if(0==ret){
            return -1;
        }
        r_total+=ret;
    }
    return 0;
}

int recv_total_show(int serfd,void* buf,int length){//循环接收至全部被接收
    char* pcur=(char*)buf;
    int r_total=0,ret;
    off_t base=length/10000;//打印间隔文件长万分之一
    off_t last_size=0;
    while(r_total<length){
        ret=recv(serfd,pcur+r_total,length-r_total,0);
        if(0==ret){
            return -1;
        }
        r_total+=ret;
        if(r_total-last_size>base){
            printf("%4.2lf%%\r",(double)r_total/length*100);
            fflush(stdout);
            last_size=r_total;
        }
    }
    printf("100.00%%\n");
    return 0;
}
//接命令
void recv_cmd(cmd_train* p,int fd){
    bzero(p,sizeof(cmd_train));
    recv(fd,&(p->datalen),4,0);
    recv(fd,&(p->cmd_type),sizeof(CMD_TYPE),0);
    if(p->datalen-8){
        recv(fd,p->buf,p->datalen-8,0);
    }
    return;
}
//发命令
void send_cmd(cmd_train* p,int fd){
    p->datalen=strlen(p->buf)+8;
    send(fd,p,p->datalen,0);
    return;
}