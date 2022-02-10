#include <stdio.h>
//求两整数间偶数平方和，奇数立方和
int main(void){
    int head,tail,e_sum,o_sum,cur;
    while(scanf("%d%d",&head,&tail)!=EOF){
        for(e_sum=0,o_sum=0,cur=head;cur<=tail;cur++){
            if(cur&1) o_sum+=(cur*cur*cur);
            else e_sum+=(cur*cur);
        }
        printf("%d %d\n",e_sum,o_sum);
    }
    return 0;
}