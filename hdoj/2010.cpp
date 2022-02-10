//水仙花数，一个三位数各位数字立方和等于其本身 有{1，153，370，371，407}
#include <stdio.h>
//给出两个数求这两个数间的水仙花数个数
int main(void){
    int low,high,i,c;
    int a[5]={1,153,370,371,407};
    while(scanf("%d%d",&low,&high)){
        for(i=0,c=0;i<5;i++){
            if(a[i]>=low&&a[i]<=high){
                printf("%d ",a[i]);
                c++;
            }
        }
        printf(c?"\n":"no\n");
    }
    return 0;
}
