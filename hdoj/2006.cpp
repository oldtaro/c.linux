#include <stdio.h>
//求奇数乘积，第一个数为个数
int main(void){
    int n,i,x,r;
    while(scanf("%d",&n)){
        for(r=1,i=0;i<n;i++){
            scanf("%d",&x);
            if(x&1) r*=x;
        }
        printf("%d\n",r);
    }
    return 0;
}