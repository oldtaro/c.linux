#include <stdio.h>
#include <string.h>

//回文串
int main(void){
    int n,i,len;
    char c[101];
    while(scanf("%d%*c",&n)!=EOF){
        for(;n>0;n--){
            memset(c,0,sizeof(c));
            gets(c);
            len=strlen(c);
            for(i=0;i<len/2;i++){
                if(c[i]!=c[len-i-1]) break;
            }
            printf(i==len/2?"Yes\n":"No\n");
        }
    }
    return 0;
}