#include <func.h>
//子线程使用主线程的栈空间
void* ThreadFunc(void* p){
    *(int*)p=10;
    printf("I am child thread, i=%d\n",*(int*)p);
}

int main(){
    int i=0;
    printf("init i=%d\n",i);
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,ThreadFunc,(void*)&i);
    if(ret!=0){
        printf("pthread_create failed\n");
        return -1;
    }
    usleep(1);
    printf("I am main thread, i=%d\n",i);
    return 0;
}