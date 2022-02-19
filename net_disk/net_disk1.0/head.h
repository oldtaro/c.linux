#ifndef __HEAD_H__
#define __HEAD_H__
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
#include <sys/sendfile.h>
#include <mysql/mysql.h>
#include <crypt.h>
#define ARGS_CHECK(argc,num) {if(argc!=num) {printf("Input ip,port,thread_num,capacity!\n");return -1;}}
#define ERROR_CHECK(ret,retval,func_name) {if(ret==retval) {printf("errno=%d,",errno);fflush(stdout);perror(func_name);return -1;}}
#define THREAD_ERR_CHECK(ret,func_name) {if(ret!=0) {printf("%s failed,%d %s\n",func_name,ret,strerror(ret));return -1;}}
#define SELFFUNC_ERR_CHECK(ret,func_name) {if(ret!=0) {printf("%s failed\n",func_name);return -1;}}

typedef struct
{
    char usr_name[50];
    char usr_pwd[100];
}usr_info,*pusr_info;
//mysql操作
//查找数据
int mysql_seek(char* table_name,char* column,char* seek_info,int res_colum,char* res_info);
//插入列值为传入值的新行
int mysql_insert(char* table_name,char* column,char* ins_value);
//数据更新
int mysql_update(char* table_name,char* column,char* cond_info,char* update_column,char* update_info);
//密码验证
int pwd_check(char* usr_name,char* usr_pwd,char* salt);
//用户注册
int usr_register(char* usr_name,char* usr_pwd);
//生成盐值
int Makesalt(char *str);
#endif