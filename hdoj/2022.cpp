#include <stdio.h>
#include <stdlib.h>

int main(void){
    int m,n,x,y,s,cur,i,j;
    while(scanf("%d%d",&m,&n)!=EOF){
        for(s=0,i=1;i<=m;i++){
            for(j=1;j<=n;j++){
                scanf("%d",&cur);
                if(abs(cur)>abs(s)){    
                    s=cur;
                    x=i;
                    y=j;
                }
            }
        }
        printf("%d %d %d\n",x,y,s);
    }
    return 0;
}