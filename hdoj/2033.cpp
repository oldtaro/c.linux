#include <stdio.h>
//时间a+b
int main(void){
    int a_time[3],rsl_time[3],n,flag;
    scanf("%d",&n);
    while(n--){
        scanf("%d%d%d%d%d%d",a_time,a_time+1,a_time+2,rsl_time,rsl_time+1,rsl_time+2);
        rsl_time[2]+=a_time[2];
        if(rsl_time[2]>59){
            rsl_time[2]-=60;
            flag=1;
        }else flag=0;
        rsl_time[1]+=(a_time[1]+flag);
        if(rsl_time[1]>59){
            rsl_time[1]-=60;
            flag=1;
        }else flag=0;
        rsl_time[0]+=(a_time[0]+flag);
        printf("%d %d %d\n",rsl_time[0],rsl_time[1],rsl_time[2]);
    }
    return 0;
}