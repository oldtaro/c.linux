#include <stdio.h>
//任意多边形面积 向量a (x0,y0), b (x1.y1)=> |axb|=2Soab
int main(void){
    int x[3],y[3],n;
    double area;
    while(scanf("%d",&n),n){
        scanf("%d%d",x,y);
        x[2]=x[0];
        y[2]=y[0];
        for(n--,area=0;n>0;n--){
            scanf("%d%d",x+1,y+1);
            area+=(double)(x[0]*y[1]-y[0]*x[1])/2;
            x[0]=x[1];
            y[0]=y[1];
        }
        area+=(double)(x[0]*y[2]-y[0]*x[2])/2;
        printf("%.1lf\n",area);
    }
    return 0;
}