#include <func.h>

int main(){
    if(!fork()){ //子进程，fork会返回两个值，子进程中fork返回0
        printf("the child pid:%d ppid=%d\n",getpid(),getppid());
        exit(0);
    }else{ //父进程，fork返回子进程id
        printf("the parent pid:%d\n",getpid());
        wait(NULL);//NULL等待所有进程,wait,waitpid都会暂停父进程，等待一个已退出子进程，并清理环境
        while(1);
    }
    return 0;
}