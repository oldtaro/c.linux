#ifndef __FUNC_H__
#define __FUNC_H__
#include "head.h"

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
//客户端状态维护
typedef struct{
    int cfd;
    int id;
    char path[200];
    int code;
    char token[20];
}client_state;
//密文
typedef struct{
    char usr_name[50];
    char salt[15];
    char usr_pwd[200];
}pwd_t;

//mysql操作
//用户表查找数据
int usrinfo_seek(char* usr_name,int res_colum,char* res_info);
//用户表插入新用户
int usrinfo_insert(char* user_name);
//用户表数据更新
int usrinfo_update(char* usr_name,char* update_column,char* update_info);
//查找子文件
int seek_child_file(int code,int usr_id,int res_colum,char* res_info);
//查找文件信息
int seek_file_info(char* cond_column,int code,int res_colum,char* res_info);
//查询下一级文件code
int next_level_file(int code,char* file_name,int res_colum,char* res_info);
//插入新文件信息
void insert_new_file(int precode,char type,int usr_id,char* file_name,int file_size,char* md5);


//密码验证
int pwd_check(pwd_t* ppt,int cfd);
//用户注册
int usr_register(pwd_t* ppt,int cfd);
//生成盐值
int Makesalt(char *str);
//接命令
void recv_cmd(cmd_train* p,int cfd);
//发命令
void send_cmd(cmd_train* p,int fd);
//短命令函数
//ls
void ls_func(client_state c_state);
//pwd
void pwd_func(client_state c_state);
//mkdir
void mkdir_func(cmd_train cmd,client_state c_state);
//cd
void cd_func(cmd_train cmd,client_state* pc_state);

#endif