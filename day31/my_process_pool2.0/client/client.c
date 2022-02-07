#include "process_pool.h"

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
    struct timeval start,end;//统计下载时间
    gettimeofday(&start,NULL);
    //1.接收文件名
    int data_len;
    char buf[1024]={0};
    ret=recv_total(serfd,&data_len,4);//接收文件名长度
    SELFFUNC_ERR_CHECK(ret,"recv_total");
    ret=recv_total(serfd,buf,data_len);//接收文件名
    SELFFUNC_ERR_CHECK(ret,"recv_total");
    int fd=open(buf,O_RDWR|O_CREAT,0666);
    //2.接收文件大小值
    ret=recv_total(serfd,&data_len,4);//接收文件大小值长度
    SELFFUNC_ERR_CHECK(ret,"recv_total");
    off_t file_size;
    ret=recv_total(serfd,&file_size,data_len);//接收文件大小值
    SELFFUNC_ERR_CHECK(ret,"recv_total");
    //3.接收文件内容
    ret=ftruncate(fd,file_size);
    ERROR_CHECK(ret,-1,"ftruncate");
    void* p=mmap(NULL,file_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ret=recv_total_show(serfd,p,file_size);
    SELFFUNC_ERR_CHECK(ret,"recv_total");
    ret=munmap(p,file_size);
    ERROR_CHECK(ret,-1,"munmap");
    gettimeofday(&end,NULL);
    printf("use time：%8.6lfs\n",(double)(end.tv_sec-start.tv_sec)+(double)(end.tv_usec-start.tv_usec)/1000000);
    close(fd);
    close(serfd);
    return 0;
}