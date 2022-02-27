#include "factory.h"
//接收命令
void recv_cmd(cmd_train* p,int fd){
    bzero(p,sizeof(cmd_train));
    recv(fd,&(p->datalen),4,0);
    recv(fd,&(p->cmd_type),sizeof(CMD_TYPE),0);
    if(p->datalen-8){//有数据才能等待接收不然会卡住
        recv(fd,p->buf,p->datalen-8,0);
    }
    return;
}
//发送命令
void send_cmd(cmd_train* p,int fd){
    p->datalen=strlen(p->buf)+8;
    send(fd,p,p->datalen,0);
    return;
}
//ls,由维护状态信息中获取code值，获取precode为此值的所有文件
void ls_func(client_state c_state){
    char file_type;
    train_t train;
    bzero(&train,sizeof(train));
    if(c_state.code){//不是在家目录下时，要判断文件类型
        seek_file_info("code",c_state.code,2,&file_type);
        if(file_type=='d'){//只能处理文件夹，文件类型不处理
            seek_child_file(c_state.code,c_state.id,4,train.buf);
            train.data_len=strlen(train.buf)+4;
            send_total(c_state.cfd,&train,train.data_len,0);
        }else{
            train.data_len=4;
            send(c_state.cfd,&train,4,0);
        }
    }else{
        seek_child_file(c_state.code,c_state.id,4,train.buf);
        train.data_len=strlen(train.buf)+4;
        send_total(c_state.cfd,&train,train.data_len,0);
    }
    return;
}
//cd 仅支持cd .. ;cd ~ ;cd 下一级
void cd_func(cmd_train cmd,client_state* pc_state){
    char code[20]={0};
    int i;
    if(strcmp(cmd.buf,"..")==0){
        if(pc_state->code){//不在根才能去上一级
            seek_file_info("code",pc_state->code,1,code);
            pc_state->code=atoi(code);
            for(i=strlen(pc_state->path)-1;pc_state->path[i]!='/';i--){
                pc_state->path[i]=0;
            }
            pc_state->path[i]=0;
        }else return;
    }else if(strcmp(cmd.buf,"~")==0){//到家目录
        pc_state->code=0;
        for(i=1;pc_state->path[i]!='/';i++);
        for(;pc_state->path[i];i++){
            pc_state->path[i]=0;
        }
    }else if(cmd.buf){//到下一级
        next_level_file(pc_state->code,cmd.buf,0,code);
        if(!code) return;//没有此文件不操作
        pc_state->code=atoi(code);
        i=strlen(pc_state->path);
        pc_state->path[i++]='/';
        strcat(pc_state->path+i,cmd.buf);
    }
    return;
}
//pwd,直接将维护的路径信息发给客户端
void pwd_func(client_state c_state){
    train_t train;
    bzero(&train,sizeof(train));
    strcpy(train.buf,c_state.path);
    puts(c_state.path);
    train.data_len=strlen(train.buf)+4;
    send_total(c_state.cfd,&train,train.data_len,0);
    return;
}
//创建文件夹
void mkdir_func(cmd_train cmd,client_state c_state){
    insert_new_file(c_state.code,'d',c_state.id,cmd.buf,4096,NULL);
    return;
}
//任务入队
void mission_inque(int epfd,client_state* pc_state,factory_t* pfac){
    epoll_del(epfd,pc_state->cfd);//注销主线程对客户端的监控
    pnode_t pcur=(pnode_t)malloc(sizeof(node_t));
    pcur->pcs=pc_state;
    pcur->next=NULL;
    pthread_mutex_lock(&(pfac->que).mutex);
    inque(&pfac->que,pcur);
    pthread_mutex_unlock(&(pfac->que).mutex);
    pthread_cond_signal(&pfac->cond);
}

//配置文件中读取ip,port
int arg_set(char* line, char* arg){	
	char* ptr = strchr(line, '=');
	if(ptr == NULL) return 0;
	strcpy(arg, ptr + 1);
    return 1;
}

int init_arg(char* ip, char* port){
	FILE* fp_conf = fopen("../conf/server.conf", "r");
	if(fp_conf == NULL) return 0;
	char line[128];
    int ret;

	bzero(line,sizeof(line));
	fgets(line, 128, fp_conf) ;
	line[strlen(line) - 1] = '\0' ;
	ret=arg_set(line, ip);
    if(!ret) return 0;

	memset(line, 0, 128);
	fgets(line, 128, fp_conf) ;
	line[strlen(line) - 1] = '\0' ;
	ret=arg_set(line, port);
    if(!ret) return 0;
	fclose(fp_conf);
    
    return 1;
}
