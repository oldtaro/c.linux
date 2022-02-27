#include "client.h"
#include "md5.h"

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
    char flag,*passwd,cmd_type[10]={0},salt[15],usr[50]={0},buf[1000];
    cmd_train cmd;
    bzero(&cmd,sizeof(cmd));
    printf("---------------net_disk_2.0---------------\n");
    printf("输入用户名：");
    scanf("%s",usr);
    passwd=getpass("输入密码：");
    printf("登录/注册，输入login/register：");
    scanf("%s",cmd_type);
    if(strcmp(cmd_type,"login")==0){
        cmd.cmd_type=LOGIN;
    }else if(strcmp(cmd_type,"register")==0){
        cmd.cmd_type=REGISTER;
    }else{
        printf("error input!\n");
        return 0;
    }

    int ret=connect(serfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
    ERROR_CHECK(ret,-1,"connnect");
    strcpy(cmd.buf,usr);
    send_cmd(&cmd,serfd);//发送登陆用户名
    printf("%s",cmd.buf);
    recv_cmd(&cmd,serfd);
    strcpy(salt,cmd.buf);
    strcpy(cmd.buf,crypt(passwd,salt));
    send_cmd(&cmd,serfd);
    recv(serfd,&flag,1,0);

    int i,offset;
    char md5[20];

    if(flag){
        printf("登陆成功！\n");
        while(1){
            printf("%s:",usr);
            bzero(buf,sizeof(buf));
            bzero(cmd_type,sizeof(cmd_type));
            bzero(&cmd,sizeof(cmd));
            scanf("%s",cmd_type);
            if(strcmp(cmd_type,"ls")==0){
                cmd.cmd_type=LS;
                send_cmd(&cmd,serfd);
                recv(serfd,&datalen,4,0);
                if(datalen-4){
                 recv(serfd,buf,datalen-4,0);
                }
                for(i=0;i<datalen-4;i++){
                    if(buf[i]!=' ') putchar(buf[i]);
                    else putchar('\n');
                }
            }else if(strcmp(cmd_type,"cd")==0){
                cmd.cmd_type=CD;
                scanf("%s",cmd.buf);
                send_cmd(&cmd,serfd);
            }else if(strcmp(cmd_type,"pwd")==0){
                cmd.cmd_type=PWD;
                send_cmd(&cmd,serfd);
                recv(serfd,&datalen,4,0);
                recv(serfd,buf,datalen-4,0);
                printf("%s\n",buf);
            }else if(strcmp(cmd_type,"mkdir")==0){
                cmd.cmd_type=MKDIR;
                scanf("%s",cmd.buf);
                send_cmd(&cmd,serfd);
            }else if(strcmp(cmd_type,"puts")==0){//只能上传当前文件夹下文件
                cmd.cmd_type=PUTS;
                send_cmd(&cmd,serfd);//通知server分配线程
                bzero(buf,sizeof(buf));
                fgets(buf,1000,stdin);
                offset=0;
                while(buf[offset]||offset<1000){
                    while(buf[offset]==' ') offset++;
                    bzero(cmd.buf,sizeof(cmd.buf));
                    sscanf(buf+offset,"%s",cmd.buf);
                    if(!cmd.buf[0]) break; 
                    send_cmd(&cmd,serfd);
                    ret=client_puts(cmd.buf,serfd);
                    offset+=strlen(cmd.buf);
                }
                bzero(cmd.buf,sizeof(cmd.buf));//结束标志
                send_cmd(&cmd,serfd);
            }

        }
    }else{
        printf("登陆失败！\n");
    }
    return 0;
}