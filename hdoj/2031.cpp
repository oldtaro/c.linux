#include <stdio.h>
#include <string.h>
#include <math.h>
//进制转换
int main(void){
    int r,x,cur,i;
    char bit_num[17]="0123456789ABCDEF";
    char trans_rsl[32];
    while(scanf("%d%d",&x,&r)!=EOF){
        memset(trans_rsl,0,sizeof(trans_rsl));
        for(cur=abs(x),i=31;cur;i--){
            trans_rsl[i]=bit_num[cur%r];
            cur=cur/r;
        }
        if(x<0) trans_rsl[i--]='-';
        for(;i<32;i++){
            printf("%c",trans_rsl[i]);
        }
        printf("\n");
    }
    return 0;
}