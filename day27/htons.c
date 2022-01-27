#include <func.h>

int main()
{
    uint16_t port=0x1234,nport;
    nport=htons(port);//主机字节序转换为网络字节序;主机为小端模式,网络字节序为大端模式
    printf("nport=%x\n",nport);
    port=0;
    port=ntohs(nport);//把网络字节序转为主机字节序
    printf("port=%x\n",port);
    return 0;
}