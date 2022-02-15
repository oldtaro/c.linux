#include <stdio.h>
//查找最大字符并在后面插入（max）输出
int main(void){
    char c[101],max;
    int i;
    while(gets(c)!=EOF){
        for(max=c[0],i=0;c[i];i++){
            if(c[i]>max) max=c[i];
        }
        for(i=0;c[i];i++){
           printf(max==c[i]?"%c(max)":"%c",c[i]);
        }
        printf("\n");
    }
    return 0;
}