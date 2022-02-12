#include <stdio.h>

int main(void){
    int n,r;
    while(scanf("%d",&n)){
        for(r=1;n>1;n--) r=(r+1)*2;
        printf("%d\n",r);
    }
    return 0;
}