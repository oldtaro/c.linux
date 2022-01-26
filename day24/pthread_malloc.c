#include <func.h>
//子线程使用main线程的堆空间
void* ThreadFunc(void* p){
    strcpy(p,"hello");
    printf("I am child thread\n");
}
int main(){
    char* p=malloc(6);
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,ThreadFunc,p);//(线程id,线程属性,线程函数指针,传参)
    if(ret!=0){
        printf("pthread_create failed\n");
        return -1;
    }
    usleep(1);
    printf("I am parent thread\n");
    printf("p=%s\n",p);
    return 0;
}