#include <stdio.h>
//求A的B次幂的末三位
int main(void){
    int rsl,a,b;
    while(scanf("%d%d",&a,&b),a||b){
        for(a=a%1000,rsl=1;b>0;b--){
            rsl=(a*rsl)%1000;
        }
        printf("%d\n",rsl);
    }
    return 0;
}