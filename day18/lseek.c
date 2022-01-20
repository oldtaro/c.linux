#include <func.h>

typedef struct student{
    int num;
    float score;
    char name[20];
}stu;

int main(int argc,char* argv[]){
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    stu s[3]={1,99,"liming",3,60,"lihua",2,49,"zhangsan"},buf;
    int i;
    for(i=0;i<3;i++){
        write(fd,&s[i].num,sizeof(s[i].num));
        write(fd,&s[i].score,sizeof(s[i].score));
        write(fd,&s[i].name,sizeof(s[i].name));
    }
    lseek(fd,0,SEEK_SET);
    for(i=0;i<3;i++){
        read(fd,&buf.num,sizeof(buf.num));
        read(fd,&buf.score,sizeof(buf.score));
        read(fd,&buf.name,sizeof(buf.name));
        printf("%-2d%5.1f %s\n",buf.num,buf.score,buf.name);
    }
    close(fd);
    return 0;
}