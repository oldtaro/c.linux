#include "work_que.h"
//队列初始化
void que_init(pque_t pque,int capacity){
    memset(pque,0,sizeof(que_t));
    pque->que_capacity=capacity;
    pthread_mutex_init(&pque->mutex,NULL);
}
//新任务入队
void inque(pque_t pque,pnode_t pnew){
    if(pque->que_size){//非空队列
        pque->tail->next=pnew;
        pque->tail=pnew;
    }else{
        pque->head=pnew;
        pque->tail=pnew;
    }
    pque->que_size++;
}
//任务出队返回客户端套接口描述符,出队只改指针减少锁间操作
void deque(pque_t pque,pnode_t* ppnode){
    if(pque->que_size){//出队的两种情况：1.任务执行结束后发现任务队列不空去取任务；2.被signal的wait线程去取任务
    //2的情况下signal后还没上锁就被1情况抢先上锁取得任务，若不判空会导致被唤醒线程再去取任务出错
        *ppnode=pque->head;
        pque->head=pque->head->next;
        pque->que_size--;
        if(!pque->que_size){
            pque->tail=NULL;
        }
    }
}
//判满
int is_que_full(que_t que){
    if(que.que_size==que.que_capacity){
        return 1;
    }else return 0;
}
//队列销毁
void que_destory(pque_t pque){

}