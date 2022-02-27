#include "client.h"
#include "md5.h"

int send_total(int cfd,void* buf,off_t length,off_t offset){//循环发送至全部被接收
    char* pcur=(char*)buf;
    off_t s_total=offset,ret;
    while(s_total<length){
        ret=send(cfd,pcur+s_total,length-s_total,0);
        if(-1==ret){//客户端断开发送失败第一次返回-1，应及时处理
            return -1;
        }
        s_total+=ret;
    }
    return 0;
}

int recv_total(int serfd,void* buf,off_t length,off_t offset){//循环接收至全部被接收
    char* pcur=(char*)buf;
    off_t r_total=offset,ret;
    while(r_total<length){
        ret=recv(serfd,pcur+r_total,length-r_total,0);
        r_total+=ret;
    }
    return 0;
}
int send_total_show(int cfd,void* buf,off_t length,off_t offset){//显示发送百分比
    char* pcur=(char*)buf;
    off_t s_total=offset,ret;
    off_t base=length/10000;//打印间隔文件长万分之一
    off_t last_size=0;
    while(s_total<length){
        ret=send(cfd,pcur+s_total,length-s_total,0);
        if(-1==ret){//客户端断开发送失败第一次返回-1，应及时处理
            return -1;
        }
        s_total+=ret;
        if(s_total-last_size>base){
            printf("%4.2lf%%\r",(double)s_total/length*100);
            fflush(stdout);
            last_size=s_total;
        }
    }
    printf("100.00%%\n");
    return 0;
}

int recv_total_show(int serfd,void* buf,off_t length,off_t offset){//循环接收至全部被接收
    char* pcur=(char*)buf;
    off_t r_total=offset,ret;
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

int client_puts(char* file_name,int serfd){
    train_t t;
    char md5[50]={0},flag;
    off_t offset;
    //1.发送文件md5码
    Compute_file_md5(file_name,md5);
    t.data_len=strlen(md5);
    strcpy(t.buf,md5);
    int ret=send_total(serfd,&t,t.data_len+4,0);
    SELFFUNC_ERR_CHECK(ret,"send_total");
    //2.发送整个文件长度
    struct stat file_stat;
    stat(file_name,&file_stat);
    t.data_len=sizeof(file_stat.st_size);
    memcpy(t.buf,&(file_stat.st_size),sizeof(file_stat.st_size));
    ret=send_total(serfd,&t,t.data_len+4,0);
    SELFFUNC_ERR_CHECK(ret,"send_total");

    recv(serfd,&flag,1,0);
    if(flag==0){
        return 0;
    }else if(flag==1){//文件池中已有未完全，接收偏移，断点续传
        recv(serfd,&offset,8,0);
    }else if(flag==2){
        offset=0;
    } 

    int fd=open(file_name,O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    
    //3.发送整个文件内容，mmap内存映射提高效率
    void* p=mmap(NULL,file_stat.st_size,PROT_READ,MAP_SHARED,fd,0);
    ret=send_total_show(serfd,p,file_stat.st_size,offset);
    SELFFUNC_ERR_CHECK(ret,"send_total");
    munmap(p,file_stat.st_size);//发送完毕解除映射
    
    return 0;
}