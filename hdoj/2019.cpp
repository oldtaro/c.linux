#include <stdio.h>
//有序数组插入
int main(void){
    int n,m,x;
    while(scanf("%d%d",&n,&m),n||m){
        for(;n>0;n--){
            scanf("%d",&x);
            if(x<m) printf("%d ",x);
            else  printf("%d %d",m,x);
        }
        printf("\n");
    }
    return 0;
}