//多项式求和
#include <stdio.h>

int main(){
    int n,m,i,j;
    double r;
    while(scanf("%d",&m)!=EOF){
        for(i=0;i<m;i++){
            scanf("%d",&n);
            for(j=1,r=0;j<=n;j++){
                r+=(double)((j&1)?1:-1)/j;
            }
            printf("%.2lf ",r);
        }
        printf("\n");
    }
    return 0;
}