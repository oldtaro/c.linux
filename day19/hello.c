#include <func.h>

int main(int argc, char* argv[]){
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    char buf[7]={0};
    int ret=sprintf(buf,"%s","hello\n");
    ERROR_CHECK(ret,-1,"sprintf");
    ret=write(fd,buf,sizeof(buf));
    ERROR_CHECK(ret,-1,"write");
    close(fd);
    return 0;
}