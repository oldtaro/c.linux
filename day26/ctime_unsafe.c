#include <func.h>

void* ThreadFunc(void* p){
    time_t now;
    time(&now);
    char* q=ctime(&now);//ctime函数中有static局部变量,不是一个线程安全函数
    printf("I am child thread, time:%s\n",q);
    sleep(3);
    printf("I am child thread, time:%s\n",q);
    return NULL;
}

int main(){
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,ThreadFunc,NULL);
    sleep(1);
    time_t now;
    time(&now);
    char* q=ctime(&now);
    printf("I am main thread, time:%s\n",q);
    pthread_join(pthid,NULL);
    return 0;
}