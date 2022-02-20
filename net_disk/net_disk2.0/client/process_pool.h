#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>
#include <strings.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <string.h>
#include <crypt.h>

#define ARGS_CHECK(argc,num) {if(argc!=num) {printf("error args\n");return -1;}}
#define ERROR_CHECK(ret,retval,func_name) {if(ret==retval) {printf("errno=%d,",errno);fflush(stdout);perror(func_name);return -1;}}
#define THREAD_ERR_CHECK(ret,func_name) {if(ret!=0) {printf("%s failed,%d %s\n",func_name,ret,strerror(ret));return -1;}}
#define SELFFUNC_ERR_CHECK(ret,func_name) {if(ret!=0) {printf("%s failed\n",func_name);return -1;}}
#define FILENAME "test"

typedef struct{
    pid_t pid;//子进程id
    int fd;//管道一端
    char busy;//忙碌标志位
}process_data_t,*pprocess_data_t;

typedef struct{
    int data_len;//火车头记录长度
    char buf[1000];//火车车厢数据
}train_t;
//命令集
typedef enum{
    REGISTER,
    LOGIN,
    TOKEN,
    LS,
    CD,
    PWD,
    MKDIR,
    REMOVE,
    GETS,
    PUTS
}CMD_TYPE;
//命令传输
typedef struct{
    int datalen;
    CMD_TYPE cmd_type;
    char buf[1000];
}cmd_train,*pcmd_train;

int mk_child(pprocess_data_t child_p,int process_num);//子进程创建
int child_mission();//子进程任务处理
int tcp_init(int* pserfd,char* ip,char* port);//tcp连接初始化
int epoll_add(int epfd, int fd);//注册epoll监控事件
int epoll_del(int epfd,int fd);//删除epoll监控事件
int send_fd(int sfd,int fd);//父进程给子进程发送描述符
int recv_fd(int sfd,int *fd);//子进程接受描述符
int trans_file(int cfd);//火车传输文件协议
int recv_total(int serfd,void* buf,int length);//循环接收文件
int recv_total_show(int serfd,void* buf,int length);//接收显示百分比
//接命令
void recv_cmd(cmd_train* p,int cfd);
//发命令
void send_cmd(cmd_train* p,int fd);