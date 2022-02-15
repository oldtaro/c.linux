#include <stdio.h>
#include <ctype.h>
#include <string.h>
//c语言合法标识符
int main(void){
    int n,i;
    char c[51];
    for(scanf("%d%*c",&n);n>0;n--){
        memset(c,0,sizeof(c));
        gets(c);//gets会读取'\n',并停止转换为'\0'
        if(isalpha(c[0])||c[0]=='_'){
            for(i=1;c[i];i++){
                if(!isalnum(c[i])&&c[i]!='_') break;
            }
            puts(c[i]?"No":"Yes");
        }else puts("No");
    }
    return 0;
}