#include <func.h>

int main(){
    if(!fork()){ //子进程，fork会返回两个值，子进程中fork返回0
        printf("the child pid:%d ppid=%d\n",getpid(),getppid());
        while(1);
    }else{ //父进程，fork返回子进程id
        printf("the parent pid:%d\n",getpid());
        exit(0);//父进程先于子进程退出，子进程成为孤儿进程，有1号祖先进程init托管，子进程退出后的清理处理由其完成
    }
    return 0;
}