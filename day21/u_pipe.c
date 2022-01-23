#include <func.h>

int main(){
    int fds[2]={0};
    pipe(fds);//无名管道在程序中由一对文件描述符表示，fds[0]读,fds[1]写
    char buf[6]={0};
    if(0==fork()){ //子进程
        close(fds[0]); //子进程写，关闭读端
        write(fds[1],"hello",6);
        close(fds[1]);// 关闭写
        exit(0);
    }else{
        close(fds[1]);//父进程关闭写
        sleep(2);//等待一段时间，确保子进程完成往管道写入
        if(read(fds[0],buf,sizeof(buf))>0){//父进程读管道内容到缓冲区
            puts(buf); 
        }
        wait(NULL);//清理子进程
        close(fds[0]);
        exit(0);
    }
}