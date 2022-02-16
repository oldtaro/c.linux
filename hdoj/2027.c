#include <stdio.h>
#include <string.h>

int main(void){
    int num[5],n,i;
    char c[101],a[6]="aeiou";
    while(scanf("%d%*c",&n)!=EOF){
        for(;n>0;n--){
            memset(num,0,sizeof(num));
            memset(c,0,sizeof(c));
            gets(c);
            for(i=0;c[i];i++){
                switch (c[i]){
                    case 'a':num[0]++;break;
                    case 'e':num[1]++;break;
                    case 'i':num[2]++;break;
                    case 'o':num[3]++;break;
                    case 'u':num[4]++;break;
                    default:break;
                }
            }
            for(i=0;i<5;i++){
                printf("%c:num%d\n",a[i],num[i]);
            }
        }
    }
    return 0;
}