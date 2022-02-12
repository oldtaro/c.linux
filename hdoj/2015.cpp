#include <stdio.h>
//偶数求和n个从2开始依序+2的数列，求其没m个的平均值，最后不够按实际数量求
int main(void){
    int n,m,count,sum,cur;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(cur=2,sum=0,count=0;n>0;n--){
            sum+=cur;
            cur+=2;
            count++;
            if(m==count){
                printf("%d ",sum/m);
                count=0;
                sum=0;
            }
        }
        if(sum){
            printf("%d",sum/count);
        }
        printf("\n");
    }
    return 0;
}