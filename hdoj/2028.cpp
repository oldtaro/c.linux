#include <stdio.h>
//求一组数的最小公倍数

int min_com_mult(int a,int b){
    int mult=1,div=1,i;
    for(i=1;i<=a;i++){
        if(a%i==0&&b%i==0) div=i;
    }
    mult=a*(b/div);
    return mult;
}

int main(void){
    int a,cur,n,i;
    while(scanf("%d",&n)!=EOF){
        for(scanf("%d",&cur);n>1;n--){
            scanf("%d",&a);
            cur=min_com_mult(a,cur);
        }
        printf("%d\n",cur);
    }
    return 0;
}