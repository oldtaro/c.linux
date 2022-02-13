#include <stdio.h>
//母牛统计，当年牛数=去年牛数+可生牛数
int main(void){
    int n;
    int cow[56]={1,2,3};
    for(n=3;n<56;n++){
        cow[n]=cow[n-1]+cow[n-3];
    }
    while(scanf("%d",&n),n!=0){
        printf("%d\n",cow[n]);
    }
    return 0;
}