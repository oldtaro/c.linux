#include <func.h>

int main(){
    if(!fork()){ //子进程，fork会返回两个值，子进程中fork返回0
        printf("the child pid:%d ppid=%d\n",getpid(),getppid());
        exit(0);//子进程先于父进程退出，父进程未及时清理子进程环境，成为僵尸进程（无法被kill，只能由父进程回收）
    }else{ //父进程，fork返回子进程id
        printf("the parent pid:%d\n",getpid());
        while(1);
    }
    return 0;
}