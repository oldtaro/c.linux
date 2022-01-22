#include <func.h>

int main(){
    if(!fork()){ //子进程，fork会返回两个值，子进程中fork返回0
        printf("the child pid:%d ppid=%d\n",getpid(),getppid());
        while(1);
    }else{ //父进程，fork返回子进程id
        printf("the parent pid:%d\n",getpid());
        while(1);
    }
    return 0;
}