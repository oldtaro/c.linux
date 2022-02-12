#include <stdio.h>
#include <math.h>
//斯塔克—黑纳格定理 n^2+n+41 在n=0,1,...,39时为质数
//欧拉质数多项式 n^2-n+41 在n=1,2,..,40时为质数

int main(void){
    int x,y,j,cur,r;
    while(scanf("%d%d",&x,&y),x||y){
        if(y<40){
            puts("OK");
        }else{
            for(x<40?x=40:x;x<=y;x++){
                r=x*x+x+41;
                cur=sqrt(r);
                for(j=2;j<=cur;j++){
                    if(0==r%j) break;
                }
                if(j<=cur) break;
            }
            puts(x>y?"OK":"Sorry");
        }
    }
    return 0;
}
