#include <func.h>

#define N 10000000

typedef struct{
    int num;//操作数
    pthread_mutex_t mutex;//线程锁
}data_t;

void* ThreadFunc(void* p){
    data_t* d=(data_t*)p;
    for(int i=0;i<N;i++){
        pthread_mutex_lock(&d->mutex);
        d->num++;
        pthread_mutex_unlock(&d->mutex);
    }
    return NULL;
}

int main(){
    data_t* d;
    d->num=0;
    pthread_t pthid;
    int ret=pthread_mutex_init(&d->mutex,NULL);//初始化锁
    ret=pthread_create(&pthid,NULL,ThreadFunc,(void*)d);
    THREAD_ERR_CHECK(ret,"pthread_create");
    for(int i=0;i<N;i++){
        pthread_mutex_lock(&d->mutex);//对d->num操作时候需上锁
        d->num++;
        pthread_mutex_unlock(&d->mutex);
    }
    ret=pthread_join(pthid,NULL);
    THREAD_ERR_CHECK(ret,"pthread_join");
    printf("the result is %d\n",d->num);
    return 0;
}