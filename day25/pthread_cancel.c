#include <func.h>

void* ThreadFunc(void* p){
    printf("I am child thred\n");//无对cancel信号的特殊处理,运行到取消点后结束
    sleep(1);
    printf("you cann't see mt\n");
    return NULL;
}

int main(){
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,ThreadFunc,NULL);
    THREAD_ERR_CHECK(ret,"pthread_create");
    ret=pthread_cancel(pthid);//向目标线程发送cancel信号,目标线程决定如何处理;即cancel时并没有free子线程资源,只是传递了一个信号
    THREAD_ERR_CHECK(ret,"pthreaa_cancel");
    ret=pthread_join(pthid,NULL);//主线程回收子线程资源
    THREAD_ERR_CHECK(ret,"pthread_join");
    printf("I am main pthread\n");
    return 0;
}