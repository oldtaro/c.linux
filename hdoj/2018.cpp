#include <stdio.h>
//母牛统计，当年牛数=去年牛数+可生牛数
int main(void){
    int i,n;
    int cow[56]={1,2,3};
    for(i=3;i<56;i++){
        cow[i]=cow[i-1]+cow[i-3];
    }
    while(scanf("%d",&n),n!=0){
        printf("%d\n",cow[n]);
    }
    return 0;
}