#include <func.h>
#define num 10000000

int main(){
    int shmid=shmget(IPC_PRIVATE,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    int* p=shmat(shmid,NULL,0);
    ERROR_CHECK(p,-1,"shmat");
    p[0]=0;
    int i;
    int semid=semget(IPC_PRIVATE,1,IPC_CREAT|0600);//创建信号量集,该集唯一信号量标识集合
    ERROR_CHECK(semid,-1,"semget");
    int ret=semctl(semid,0,SETVAL,1);//(集合标识,信号量编号,操作,设定值)
    ERROR_CHECK(ret,-1,"semctl");
    struct sembuf sp,sv;//sembuf中成员：sem_num信号量编号,sem_op一次操作改变信号量的值,sem_flg
    sp.sem_num=0;
    sp.sem_op=-1;//p操作信号量减一
    sp.sem_flg=SEM_UNDO;//程序结束,信号量为操作前值
    sv.sem_num=0;
    sv.sem_op=1;//v操作信号量加一
    sv.sem_flg=SEM_UNDO;
    if(!fork()){
        for(i=0;i<num;i++){
            semop(semid,&sp,1);//先p后v,互斥访问共享内存
            p[0]++;
            semop(semid,&sv,1);
            }
    }else{
        for(i=0;i<num;i++){
            semop(semid,&sp,1);
            p[0]++;
            semop(semid,&sv,1);
        }
        wait(NULL);
        printf("the result=%d\n",p[0]);
    }
    return 0;
}