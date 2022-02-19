#include <stdio.h>
//判定是否为真约数
int main(void){
    int n,i,x,y,sum1,sum2;
    scanf("%d",&n);
    while(n--){
        scanf("%d%d",&x,&y);
        for(i=1,sum1=0;i<=x/2;i++){
            if(x%i==0) sum1+=i;
        }
        for(i=1,sum2=0;i<=y/2;i++){
            if(y%i==0) sum2+=i;
        }
        printf(x==sum2&&y==sum1?"Yes\n":"No\n");
    }
}