#include <stdio.h>

//集合A减集合B =>A-AB
int main(void){
    int i,j,n,m,a[100],b[100],flag;
    while(scanf("%d%d",&n,&m),n||m){
        for(i=0;i<n;i++){
            scanf("%d",a+i);
        }
        for(i=0;i<m;i++){
            scanf("%d",b+i);
        }
        for(i=0,flag=0;i<n;i++){
            for(j=0;j<m;j++){
                if(a[i]==b[j]) break;
            }
            if(j==m){
                printf(i<n-1?"%d ":"%d\n",a[i]);
                flag=1;
            }
        }
        if(0==flag) printf("NULL\n");
    }
    return 0;
}