#include <stdio.h>
//三条边能否构成三角形
int main(void){
    int x[3],n,i,max;
    scanf("%d",&n);
    while(n--){
        scanf("%d%d%d",x,x+1,x+2);
        for(i=1,max=0;i<3;i++){
            if(x[i]>x[max]) max=i;
        }
        printf(x[max]<(x[0]+x[1]+x[2]-x[max])?"Yes\n":"No\n");
    }
    return 0;
}