#include <stdio.h>
#include <stdlib.h>

int main(void){
    int n,i;
    double sum,min,max,cur;
    while(scanf("%d",&n)!=EOF){
        for(i=0,sum=0;i<n;i++){
            if(i){
                scanf("%lf",&cur);
                sum+=cur;
                if(cur>max) max=cur;
                if(cur<min) min=cur;
            }else{
                scanf("%lf",&sum);
                min=sum;
                max=sum;
            }
        }
        printf("%.2lf\n",(sum-min-max)/(double)(n-2));
    }
    return 0;
}