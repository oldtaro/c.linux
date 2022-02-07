#include "process_pool.h"

int trans_file(int cfd){
    train_t t;
    //1.发送文件名
    t.data_len=sizeof(FILENAME);
    strcpy(t.buf,FILENAME);
    int ret=send_total(cfd,&t,t.data_len+4);
    SELFFUNC_ERR_CHECK(ret,"send_total");
    int fd=open(FILENAME,O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    //2.发送整个文件长度
    struct stat file_stat;
    stat(FILENAME,&file_stat);
    t.data_len=sizeof(file_stat.st_size);
    memcpy(t.buf,&(file_stat.st_size),sizeof(file_stat.st_size));
    ret=send_total(cfd,&t,t.data_len+4);
    SELFFUNC_ERR_CHECK(ret,"send_total");
    //3.发送整个文件内容，mmap内存映射提高效率
    void* p=mmap(NULL,file_stat.st_size,PROT_READ,MAP_SHARED,fd,0);
    ret=send_total(cfd,p,file_stat.st_size);
    SELFFUNC_ERR_CHECK(ret,"send_total");
    munmap(p,file_stat.st_size);//发送未必解除映射
    close(cfd);
}

int send_total(int cfd,void* buf,int length){//循环发送至全部被接收
    char* pcur=(char*)buf;
    int s_total=0,ret;
    while(s_total<length){
        ret=send(cfd,pcur+s_total,length-s_total,0);
        if(-1==ret){//客户端断开发送失败第一次返回-1，应及时处理
            return -1;
        }
        s_total+=ret;
    }
    return 0;
}

int recv_total(int serfd,void* buf,int length){//循环接收至全部被接收
    char* pcur=(char*)buf;
    int r_total=0,ret;
    while(r_total<length){
        ret=recv(serfd,pcur+r_total,length-r_total,0);
        r_total+=ret;
    }
    return 0;
}