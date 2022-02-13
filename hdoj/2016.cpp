#include <stdio.h>
#define swap(a,b) {int temp;temp=a;a=b;b=temp;}
//交换一组数中最小的数和第一个元素的位置
int main(void){
    int arr[100]={0};
    int n,min,i;
    while(scanf("%d",&n),n!=0){
        for(min=0,i=0;i<n;i++){
            scanf("%d",arr+i);
            if(arr[i]<arr[min]){
                min=i;
            }
        }
        swap(arr[0],arr[min]);
        for(i=0;i<n;i++){
            printf(i<(n-1)?"%d ":"%d\n",arr[i]);
        }
    }
    return 0;
}