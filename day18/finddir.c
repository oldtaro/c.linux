#include <func.h>

int print(char* path, int deep){
    DIR* dir;
    dir=opendir(path);
    struct dirent* p;
    char buf[1024];
    while(p=readdir(dir)){
        if(!strcmp(".",p->d_name)||!strcmp("..",p->d_name)){}
        else{
            printf("%*s%s\n",deep," ",p->d_name);
            if(p->d_type==4){
                memset(buf,0,sizeof(buf));
                sprintf(buf,"%s%s%s",path,"/",p->d_name);
                print(buf,deep+4);
            }
        }
    }
}

int main(int argc,char* argv[]){
    ARGS_CHECK(argc,2);
    print(argv[1],0);
    return 0;
}