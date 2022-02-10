#include <stdio.h>
#define PI 3.1415927
//球的体积
int main(void){
    double x;
    while(scanf("%lf",&x)!=EOF){
        printf("%.3lf\n",(x*x*x*PI*4)/3);
    }
    return 0;
}