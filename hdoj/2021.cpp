#include <stdio.h>

int main(void){
    int n,m,x,i;
    while(scanf("%d",&n),n){
        for(x=0;n>0;n--){
            scanf("%d",&m);
            x+=m/100;
            m=m%100;
            x+=m/50;
            m=m%50;
            x+=m/10;
            m=m%10;
            x+=m/5;
            m=m%5;
            x+=m/2;
            m=m%2;
            x+=m;
        }
        printf("%d\n",x);
    }
    return 0;
}