#include <func.h>

int main(int argc, char* argv[]){
    ARGS_CHECK(argc,2);
    DIR* dir=opendir(argv[1]);
    if(NULL==dir){
        perror("opendir");
        return -1;
    }
    struct dirent* p;
    while(p=readdir(dir)){    //readdir后会移动到下一文件
        printf("inode=%ld ,reclen=%d ,type=%c, name=%s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);
    }
    closedir(dir);
    return 0;
}