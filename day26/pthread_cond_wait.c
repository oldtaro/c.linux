#include <func.h>

typedef struct{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}lock;

void* ThreadFunc(void* p){
    printf("I am child thread, will wait\n");
    lock* l=(lock*)p;
    pthread_mutex_lock(&l->mutex);//排队时应互斥
    pthread_cond_wait(&l->cond,&l->mutex);//上半部:上锁,排队,解锁,睡觉待唤醒;下半部:醒来,上锁,出队,解锁
    pthread_mutex_unlock(&l->mutex);
    printf("I am child thread, wake up\n");
    return NULL;
}

int main(){
    lock* l;
    pthread_t pthid;
    int ret;
    ret=pthread_mutex_init(&l->mutex,NULL);
    THREAD_ERR_CHECK(ret,"pthread_mutex_init");
    ret=pthread_cond_init(&l->cond,NULL);
    THREAD_ERR_CHECK(ret,"pthread_cond_init");
    ret=pthread_create(&pthid,NULL,ThreadFunc,(void*)l);
    THREAD_ERR_CHECK(ret,"pthread_create");
    sleep(1);//防止signal时,子线程还未wait,不能够获取信号而导致死锁,实际中创建子线程与signal之间有多个操作不会出现这种情况
    ret=pthread_cond_signal(&l->cond);
    THREAD_ERR_CHECK(ret,"pthread_cond_signal");
    ret=pthread_join(pthid,NULL);
    THREAD_ERR_CHECK(ret,"pthread_join");
    return 0;
}