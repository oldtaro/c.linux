#include <stdio.h>
//成绩转换

int main(void){
    int x;
    while(scanf("%d",&x)!=EOF){
        if(x>100||x<0){
            printf("Score is error\n");
        }else if(x>=90){
            printf("A\n");
        }else if(x>=80){
            printf("B\n");
        }else if(x>=70){
            printf("C\n");
        }else if(x>=60){
            printf("D\n");
        }else{
            printf("E\n");
        }
    }
    return 0;
}