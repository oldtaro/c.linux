#include <stdio.h>
#include <string.h>
//杨辉三角
int main(void){
    int n,i,j,arr[31],pre,temp;
    while(scanf("%d",&n)!=EOF){
        memset(arr,0,sizeof(arr));
        for(arr[0]=1,i=1;i<=n;i++){
            printf("%d ",arr[0]);
            for(j=1,pre=1;j<i;j++){
                temp=arr[j];
                arr[j]=pre+arr[j];
                pre=temp;
                printf("%d ",arr[j]);
            }
            printf("\n");
        }
    }
}