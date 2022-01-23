#include <func.h>

int main(){
    if(fork()!=0){
        exit(0);//父进程退出，成为孤儿进程
    }
    setsid();//成立新会话，成为新进程组组长新会话组的领导，脱离控制终端
    chdir("/");//设置工作目录为根目录
    umask(0);//重设文件访问权限掩码为0
    for(int i=0;i<3;i++){//关闭从父进程继承而来的无关文件
        close(i);
    }
    int fd=open("/tmp/log",O_RDWR|O_CREAT,0600);
    char buf[12]="wohenshuai\n";
    while(1){
        write(fd,buf,sizeof(buf));
        sleep(2);
    }
    return 0;
}