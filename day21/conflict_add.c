#include <func.h>
#define num 10000000

int main(){
    int shmid=shmget(IPC_PRIVATE,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    int* p=shmat(shmid,NULL,0);
    ERROR_CHECK(p,(char*)-1,"shmat");
    p[0]=0;
    int i;
    if(!fork()){
        for(i=0;i<num;i++){
            p[0]++;
        }
    }else{
        for(i=0;i<num;i++){
            p[0]++;
        }
        wait(NULL);
        printf("p[0]=%d\n",p[0]);
    }
    return 0;
}