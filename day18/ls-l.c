#include <func.h>

int main(int argc,char* argv[]){
    ARGS_CHECK(argc,2);
    DIR* dir;
    struct dirent* p;
    struct stat buf;
    char date[1024];
    dir=opendir(argv[1]);
    int cur_mode,i;
    while(p=readdir(dir)){
        if(!strcmp(".",p->d_name)||!strcmp("..",p->d_name)){
        }else{
        if(p->d_type==4){ //d_type为4，是目录文件
        printf("d");
        }else{
            printf("-");
        }
        if(!stat(p->d_name,&buf)){
            cur_mode=buf.st_mode; //获得当前文件的权限信息
            for(i=1<<8;i>0;){
                if(i&cur_mode){
                    printf("r");
                }else{
                    printf("-");
                }
                i=i>>1;
                if(i&cur_mode){
                    printf("w");
                }else{
                    printf("-");
                }
                i=i>>1;
                if(i&cur_mode){
                    printf("x");
                }else{
                    printf("-");
                }
                i=i>>1;
            }
            memset(date,0,sizeof(date));
            strcpy(date,ctime(&buf.st_mtime)+4);//去掉星期
            date[strlen(date)-9]='\0';         //去掉年份秒数
            printf("%2ld %5s %5s %5ld %s %s\n",buf.st_nlink,getpwuid(buf.st_uid)->pw_name,
            getgrgid(buf.st_gid)->gr_name,buf.st_size,date,p->d_name);
            }
        }
    }
    return 0;
}