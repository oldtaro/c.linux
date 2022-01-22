#include <func.h>

int main(int argc, char* argv[]){
    ARGS_CHECK(argc,3);
    int i=atoi(argv[1]);
    int j=atoi(argv[2]);
    printf("i+j=%d\n",i+j);
    return 0;
}