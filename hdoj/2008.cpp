#include <stdio.h>
//第一个数为个数，统计大于0，小于0，等于0的数个数
int main(void){
    int n,p_count,z_count,m_count,i;
    double x;
    while(scanf("%d",&n)!=EOF){
        for(p_count=0,z_count=0,m_count=0,i=0;i<n;i++){
            scanf("%lf",&x);
            if(x>0) p_count++;
            else if(x<0) m_count++;
            else z_count++;
        }
        printf("%d %d %d\n",m_count,z_count,p_count);
    }
    return 0;
}