//数列第一项为整数n,以后各项为前一项的平方根，第二个数为m求前m项和
#include <stdio.h>
#include <math.h>

int main(void){
    int n,m,i;
    double r,cur;
    while(scanf("%d%d",&n,&m)){
        for(cur=n,r=0,i=0;i<m;i++){
            r+=cur;
            cur=sqrt(cur);
        }
        printf("%.2lf\n",r);
    }
    return 0;
}