#include <func.h>

void* ThreadFunc(void* p){
    printf("I am child, the arg is %ld\n",(long)p);
    pthread_exit((void*)2);//子线程退出时2会作为返回值被join函数所捕获
}

int main(){
    long pthret;
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,ThreadFunc,(void*)1);//64位,指针大小为8b,要以强转为long型输出
    THREAD_ERR_CHECK(ret,"pthread_create");
    pthread_join(pthid,(void**)&pthret);//阻塞函数,等到指定线程返回;exit返回的是一个指针,所以要用二级指针来改变其值
    printf("I am main thread,the child thread's ret=%ld\n",pthret);
    return 0;
}