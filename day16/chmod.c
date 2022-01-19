#include <func.h>

int main(int argc,char* argv[]){
    if(argc!=2){
        printf("args error");
        return -1;
    }
    char buf[1024];
    memset(buf,0,sizeof(buf));
    getcwd(buf,sizeof(buf)); //获取当前路径
    puts(buf);
    int ret;
    ret=chmod(argv[1],0666);
    if(-1==ret){
        perror("chmod");
        return -1;
    }
    return 0;
}
