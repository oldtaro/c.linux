#include <func.h>
//将标准输出重定向到log1文件
int main(int argc, char* argv[]){
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR);//程序打开文件就默认打开了0，1，2（标准输入，标准输出，标准错误输出）
    //此处fd为3
    printf("fd=%d",fd);
    ERROR_CHECK(fd,-1,"open");
    printf("\n");//刷新标准输出
    close(STDOUT_FILENO);//关闭标准输出stdout，此时1号fd为空
    int fd1=dup(fd);//dup文件描述符的复制，产生一个新的描述符指向同一个文件对象，其引用计数加1
    //dup产生当前未打开最小描述符，fd1为1，重定向到了标准输出
    printf("fd1=%d\n",fd1);
    close(fd);
    printf("the out of stdout\n");
    return 0;
}