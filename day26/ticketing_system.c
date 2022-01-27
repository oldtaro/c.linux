#include <func.h>

#define N 50

typedef struct{
    int ticket;//票数
    int sit;//余座
    pthread_mutex_t mutex; //互斥修改票数
    pthread_cond_t cond;
}tic;
//卖票线程
void* SaleThread1(void* p){
    tic* t=(tic*)p;
    while(1){
        pthread_mutex_lock(&t->mutex);
        if(t->ticket>0){
            t->ticket--;
            if(t->ticket==0&&t->sit>0)//票卖完还有座位出票
                pthread_cond_signal(&t->cond);
            pthread_mutex_unlock(&t->mutex);
            printf("I am SaleThread1:\nSold 1 ticket,remain %d tickets, %d sits\n",t->ticket,t->sit);
            sleep(2);
        }else if(t->ticket==0&&t->sit==0){//无票无座退出
            pthread_mutex_unlock(&t->mutex);
            printf("I am SaleThread1,tickets sold out!\n");
            break;
        }
    }
    return NULL;
}
        
        
void* SaleThread2(void* p){
    tic* t=(tic*)p;
    while(1){
        pthread_mutex_lock(&t->mutex);
        if(t->ticket>0){
            t->ticket--;
            if(t->ticket==0&&t->sit>0)//票卖完还有座位出票
                pthread_cond_signal(&t->cond);
            pthread_mutex_unlock(&t->mutex);
            printf("I am SaleThread2:\nSold 1 ticket,remain %d tickets, %d sits\n",t->ticket,t->sit);
            sleep(2);
        }else if (t->ticket==0&&t->sit==0){//无票无座退出
            pthread_mutex_unlock(&t->mutex);
            printf("I am SaleThread2,tickets sold out!\n");
            break;
        }
    }
    return NULL;
}

//放票线程
void* SetThread(void* p){
    tic* t=(tic*)p;
    while(1){
        pthread_mutex_lock(&t->mutex);
        if(t->sit>0){//有空位有票时等待
            if(t->ticket>0)
                pthread_cond_wait(&t->cond,&t->mutex);
            t->ticket+=10;
            t->sit-=10;
            pthread_mutex_unlock(&t->mutex);
            printf("Set 10 tickets.\n");
        }else{
            pthread_mutex_unlock(&t->mutex);
            break;
        }
    }
    return NULL;
}

int main(){
    tic* t;
    pthread_t sapthid1,sapthid2,septhid;
    int ret;
    t->ticket=0;
    t->sit=N;
    ret=pthread_mutex_init(&t->mutex,NULL);
    THREAD_ERR_CHECK(ret,"pthread_mutex_init");
    ret=pthread_cond_init(&t->cond,NULL);
    THREAD_ERR_CHECK(ret,"pthread_cond_init");
    ret=pthread_create(&septhid,NULL,SetThread,(void*)t);
    THREAD_ERR_CHECK(ret,"pthread_create");
    ret=pthread_create(&sapthid1,NULL,SaleThread1,(void*)t);
    THREAD_ERR_CHECK(ret,"pthread_crearte");
    ret=pthread_create(&sapthid2,NULL,SaleThread2,(void*)t);
    THREAD_ERR_CHECK(ret,"pthread_create");
    ret=pthread_join(septhid,NULL);
    THREAD_ERR_CHECK(ret,"pthread_join");
    ret=pthread_join(sapthid1,NULL);
    THREAD_ERR_CHECK(ret,"pthread_join");
    ret=pthread_join(sapthid2,NULL);
    THREAD_ERR_CHECK(ret,"pthread_join");
    ret=pthread_mutex_destroy(&t->mutex);
    THREAD_ERR_CHECK(ret,"pthread_mutex_destory");
    ret=pthread_cond_destroy(&t->cond);
    THREAD_ERR_CHECK(ret,"pthread_cond_destory");
    return 0;
}