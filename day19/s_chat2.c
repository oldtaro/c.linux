#include <func.h>

int main(int argc, char* argv[]){
   ARGS_CHECK(argc, 3);
   int fdr,fdw;
   fdw=open(argv[1],O_WRONLY);//chat2管道1的写端
   ERROR_CHECK(fdw,-1,"open");
   fdr=open(argv[2],O_RDONLY);//chat2管道2的读端
   ERROR_CHECK(fdr,-1,"open");
    printf("I am chat2\n");
    char buf[1024];
    fd_set rdset;//内核读操作的描述符集合
    int ret;
    int ready_fdnum;
    while(1){
        FD_ZERO(&rdset);//将描述符集清零
        FD_SET(STDIN_FILENO,&rdset);//将标准输入加入读集
        FD_SET(fdr,&rdset);//将管道2的读端加入读集
        ready_fdnum=select(fdr+1,&rdset,NULL,NULL,NULL);//(最大文件描述符(实际+1)，读集，写集，异常操作集，等待时间)
        if(FD_ISSET(STDIN_FILENO,&rdset)){//此时读集合中标准输入是否有数据
            memset(buf,0,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            ERROR_CHECK(ret,-1,"read");
            write(fdw,buf,sizeof(buf));//写入1号管道
        }
        if(FD_ISSET(fdr,&rdset)){//2号管道有数据
            memset(buf,0,sizeof(buf));
            ret=read(fdr,buf,sizeof(buf));
            ERROR_CHECK(ret,-1,"read");
            if(0==ret){
                printf("byebye\n");
                break;
            }
            printf("%s",buf);//把2号管道内容写入buf后输出
        }
    }
    close(fdr);
    close(fdw);
    return 0;
}