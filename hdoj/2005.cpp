#include <stdio.h>
//输入日期输出该年第几天
int main(void){
    int y,m,d,i,days;
    int month[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    while(scanf("%d/%d/%d",&y,&m,&d)!=EOF){
        for(days=0,i=0;i<m-1;i++){
            days+=month[i];
        }
        days+=d;
        if(m>2){
            days+=(y%4==0&&y%100!=0||y%400==0);
        }
        printf("%d\n",days);
    }
    return 0;
}