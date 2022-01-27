#include <func.h>

int main(int argc,char* argv[]){
    ARGS_CHECK(argc,2);
    struct in_addr myaddr;
    int ret=inet_aton(argv[1],&myaddr);//将点分十进制的IP地址转换为32位二进制数的网络字节序
    if(ret==0){
        printf("error ip!\n");
        return -1;
    }
    printf("inet_aton result:%x\n",myaddr.s_addr);
    printf("inet_addr reslut:%x\n",inet_addr(argv[1]));//inet_addr直接返回网络字节序,功能同inet_aton
}