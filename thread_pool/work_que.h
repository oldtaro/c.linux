#ifndef __WORK_QUE_H__
#define __WORK_QUE_H__
#include "head.h"
//任务结点
typedef struct que_node{
    int cfd;//客户端套接口描述符
    struct que_node* next;
}node_t,*pnode_t;

//任务队列
typedef struct work_que{
    pnode_t head,tail;
    int que_size;
    int que_capacity;//服务器接收任务的能力，防止队列过长后面任务得不到响应
    pthread_mutex_t mutex;//互斥修改队列信息
}que_t,*pque_t;

//初始化队列
void que_init(pque_t pque,int capacity);
//新任务入队
void inque(pque_t pque,pnode_t pnew);
//出队
void deque(pque_t pque,pnode_t* ppnode);
//判满
int is_que_full(que_t que);
//队列销毁
void que_destory(pque_t pque);
#endif