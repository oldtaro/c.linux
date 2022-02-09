#include <stdio.h>
#include <math.h>
//abs
int main(void){
    double a;
    while(scanf("%lf",&a)!=EOF){
        printf("%.2lf\n",fabs(a));
    }
    return 0;
}