#include <func.h>

int main(){
    char buf[1024];
    memset(buf,0,sizeof(buf));
    getcwd(buf,sizeof(buf));
    puts(buf);
    chdir("../");
    memset(buf,0,sizeof(buf));
    getcwd(buf,sizeof(buf));
    puts(buf);
}
