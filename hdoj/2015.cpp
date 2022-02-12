#include <stdio.h>
//偶数求和
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