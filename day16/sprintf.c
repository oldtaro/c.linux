#include <func.h>

typedef struct student{
    int num;
    float score;
    char name[20];
}stu;

int main(){
    stu s={1,59.9,"liming"};
    char buf[1024];
    sprintf(buf,"%d,%f,%s",s.num,s.score,s.name);
    puts(buf);
    return 0;
}
