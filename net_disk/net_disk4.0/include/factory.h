#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"
#include "func.h"
//线程池
typedef struct factory{
    int epfd;//epoll监控集
    que_t que;//任务队列
    pthread_cond_t cond;//条件变量
    pthread_t* pthid;//线程id
    char start_flag;//线程启动标志，防止重复启动
}factory_t,*pfactory_t;
//文件传输火车
typedef struct{
    int data_len;
    char buf[1000];
}train_t;

//初始化
void factory_init(pfactory_t pf,int thread_num,int capacity);
//启动线程池
int factory_start(pfactory_t pf,int thread_num);
//线程任务
void* thread_mission(void* pf);
//tcp连接初始化
int tcp_init(int* pserfd,char* ip,char* port);
//注册epoll监控事件
int epoll_add(int epfd, int fd);
//删除epoll监控事件
int epoll_del(int epfd,int fd);
//文件传输协议
//客户端上传文件
int usr_puts_file(int cfd,char* md5,off_t* pfile_size);
//客户端下载文件
int usr_gets_file(int cfd,char*md5);
//循环发送至全部接收
int send_total(int cfd,void* buf,off_t length,off_t offset);
//循环接收至全部接收
int recv_total(int serfd,void* buf,off_t length,off_t offset);
//--------------------------------------------------------------------
//任务入队
void mission_inque(int epfd,client_state* pc_state,factory_t* pfac);

#endif