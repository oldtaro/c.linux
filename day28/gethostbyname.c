#include <func.h>

int main(int argc,char* argv[]){
    ARGS_CHECK(argc,2);
    struct hostent* h;
    h=gethostbyname(argv[1]);
    if(h==NULL){
        printf("error name!\n");
    }
    printf("正式主机名:%s\n",h->h_name);
    int i;
    printf("别名:");
    for(i=0;h->h_aliases[i]!=NULL;i++){//有多个别名以二维数组存储
        printf("%s\n",h->h_aliases[i]);
    }
    printf("IP地址类型:%d\n",h->h_addrtype);
    printf("IP地址长:%d\n",h->h_length);
    char dst[100];
    for(i=0;h->h_addr_list[i];i++){//有多个IP,以网络字节序存储
        bzero(dst,sizeof(dst));
        inet_ntop(h->h_addrtype,h->h_addr_list[i],dst,sizeof(dst));//网络字节序转换为点分十进制
        puts(dst);
    }
}