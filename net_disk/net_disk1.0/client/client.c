#include "process_pool.h"

int main(int argc,char* argv[]){
    ARGS_CHECK(argc,3);
    int serfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in ser_addr;
    bzero(&ser_addr,sizeof(ser_addr));
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_port=htons(atoi(argv[2]));
    ser_addr.sin_addr.s_addr=inet_addr(argv[1]);
    socklen_t addrlen=sizeof(ser_addr);

    int datalen;
    char flag;
    usr_info usr;
    bzero(&usr,sizeof(usr));
    printf("注册用户登陆，未注册用户将直接注册\n输入用户名：");
    scanf("%s",usr.usr_name);
    printf("输入密码：");
    scanf("%s",usr.usr_pwd);

    int ret=connect(serfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
    ERROR_CHECK(ret,-1,"connnect");
    datalen=strlen(usr.usr_name);
    send(serfd,&datalen,4,0);
    send(serfd,usr.usr_name,datalen,0);
    datalen=strlen(usr.usr_pwd);
    send(serfd,&datalen,4,0);
    send(serfd,usr.usr_pwd,datalen,0);
    
    recv(serfd,&flag,1,0);
    if(flag){
        printf("登陆成功！\n");
    }else{
        printf("登陆失败！\n");
    }
    
}