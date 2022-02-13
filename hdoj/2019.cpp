#include <stdio.h>
#include <string.h>
//有序数组插入
int main(void){
    int n,m,x,i;
    int arr[101];
    while(scanf("%d%d",&n,&m),n||m){
        memset(arr,0,sizeof(arr));
        for(i=0,x=0;i<n;i++){
            scanf("%d",arr+i);
            if(arr[i]<m) x++;
        }
        for(i=n;i>x;i--)
            arr[i]=arr[i-1];
        arr[x]=m;
        for(i=0;i<n+1;i++)
            printf(i==n?"%d\n":"%d ",arr[i]);
    }
    return 0;
}