#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//输入数据包含多个测试实例，每个测试实例的第一行只有一个整数 n(n<=100)，表示你喜欢
//看的节目的总数，然后是 n 行数据，每行包括两个数据 Ti_s,Ti_e (1<=i<=n)，分别表示第 i 个
//节目的开始和结束时间，为了简化问题，每个时间都用一个正整数表示。n=0 表示输入结
//束，不做处理。
typedef struct{
    int start;
    int end;
}time_node;

int compare(const void* left,const void* right){
    time_node* p1=(time_node*)left;
    time_node* p2=(time_node*)right;
    return p1->end-p2->end;
}

int main(void){
    time_node t[100];
    int n,i,j,count;
    while(scanf("%d",&n),n){
        memset(t,0,sizeof(t));
        for(i=0;i<n;i++){
            scanf("%d%d",&t[i].start,&t[i].end);
        }
        qsort(t,n,sizeof(time_node),compare);
        for(i=1,j=0,count=1;i<n;i++){
            if(t[j].end<=t[i].start){
                count++;
                j=i;
            }
        }
        printf("%d\n",count);
    }
    return 0;
}