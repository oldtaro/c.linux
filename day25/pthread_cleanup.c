#include <func.h>

void cleanup(void* p){
    printf("I am cleanup%ld\n",(long)p);
}

void* ThreadFunc(void* p){
    pthread_cleanup_push(cleanup,(void*)1);//清理函数,传参;清理函数push,pop必须成对出现
    pthread_cleanup_push(cleanup,(void*)2);
    sleep(1);
    pthread_cleanup_pop(0);//pop(非零值)按栈序执行清理函数并注销该函数
    pthread_cleanup_pop(0);//pop(0)仅在线程自身调用exit,或其它线程对其调用cancel时才弹出清理函数并执行
    return NULL;
}

int main(){
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,ThreadFunc,NULL);
    THREAD_ERR_CHECK(ret,pthread_create);
    ret=pthread_cancel(pthid);
    THREAD_ERR_CHECK(ret,pthread_cancel);
    ret=pthread_join(pthid,NULL);
    THREAD_ERR_CHECK(ret,pthread_join);
    return 0;
}