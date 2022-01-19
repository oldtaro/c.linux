#include <func.h>

typedef struct student{
    int num;
    float score;
    char name[20];
}stu;

int main(){
    stu s={0};
    char buf[1024]="1 59.9 liming";
    sscanf(buf,"%d%f%s",&s.num,&s.score,s.name);
    printf("%d,%f,%s",s.num,s.score,s.name);
    return 0;
}
