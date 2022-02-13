#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//绝对值排序
int partition(int* arr,int low,int high){
    int pivot=abs(arr[low]);
    while(low<high){
        while(low<high&&abs(arr[high])>=pivot) high--;
        arr[low]=arr[high];
        while(low<high&&abs(arr[low])<=pivot) low++;
        arr[high]=arr[low];
    }
    arr[low]=pivot;
    return low;
}
void quick_sort(int* arr,int low,int high){
    if(low<high){
        int temp=partition(arr,low,high);
        quick_sort(arr,low,temp-1);
        quick_sort(arr,temp+1,high);
    }
    return;
}
int main(void){
    int n,i,arr[100];
    while(scanf("%d",&n),n){
        memset(arr,0,sizeof(arr));
        for(i=0;i<n;i++) scanf("%d",arr+i);
        quick_sort(arr,0,n-1);
        for(i=0;i<n;i++) printf("%d ",arr[i]);
        printf("\n");
    }
    return 0;
}