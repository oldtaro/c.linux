#include <func.h>

int main(){
    execl("./add","add","3","4",NULL);//NULL标志调用结束
    return 0;
}