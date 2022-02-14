#include <stdio.h>

int main(void){
    int stu_score[50][5],stu,sbj;
    float stu_avg[50],sbj_avg[5];
    int i,j,stu_sum,sbj_sum,n;
    while(scanf("%d%d",&stu,&sbj)!=EOF){
        for(i=0;i<stu;i++){
            for(stu_sum=0,j=0;j<sbj;j++){
                scanf("%d",&stu_score[i][j]);
                stu_sum+=stu_score[i][j];
            }
            stu_avg[i]=(float)stu_sum/sbj;
        }
        for(i=0;i<stu;i++){
            printf(i!=(stu-1)?"%.2f ":"%.2f\n",stu_avg[i]);
        }
        for(j=0;j<sbj;j++){
            for(sbj_sum=0,i=0;i<stu;i++){
                sbj_sum+=stu_score[i][j];
            }
            sbj_avg[j]=(float)sbj_sum/stu;
        }
        for(j=0;j<sbj;j++){
            printf(j!=(sbj-1)?"%.2f ":"%.2f\n",sbj_avg[j]);
        }
        for(n=0,i=0;i<stu;i++){
            for(j=0;j<sbj;j++){
                if(stu_score[i][j]<sbj_avg[j]) break;
            }
            if(j==(sbj)) n++;
        }
        printf("%d\n",n);
    }
    return 0;
}