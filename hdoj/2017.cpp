#include <stdio.h>
#include <ctype.h>
//字符统计
int main(void){
    int n,dig_num;
    char c;
    while(scanf("%d%*c",&n)!=EOF){
        for(;n>0;n--){
            dig_num=0;
            while((c=getchar())!='\n'){
                if(isdigit(c)) dig_num++;
            }
            printf("%d\n",dig_num);
        }
    }
    return 0;
}