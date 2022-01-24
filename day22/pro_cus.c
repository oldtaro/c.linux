#include <func.h>

int main(){
    int semid=semget(IPC_PRIVATE,2,IPC_CREAT|0600);
    ERROR_CHECK(semid,-1,"semget");
    unsigned short arr[2]={0,10};
    int ret=semctl(semid,0,SETALL,arr);
    ERROR_CHECK(ret,-1,"semctl");
    if(!fork()){//子进程为消费者
        struct sembuf spfull,svempty;
        spfull.sem_num=0;//p(full)
        spfull.sem_op=-1;
        spfull.sem_flg=SEM_UNDO;
        svempty.sem_num=1;//v(empty)
        svempty.sem_op=1;
        svempty.sem_flg=SEM_UNDO;
        while(1){
            printf("我是消费者 产品:%d 空位:%d\n",semctl(semid,0,GETVAL),semctl(semid,1,GETVAL));
            semop(semid,&spfull,1);
            printf("消费\n");
            semop(semid,&svempty,1);
            printf("我是消费者 产品:%d 空位:%d\n",semctl(semid,0,GETVAL),semctl(semid,1,GETVAL));
            sleep(3);
        }
    }else{
        struct sembuf svfull,spempty;
        svfull.sem_num=0;//v(full)
        svfull.sem_op=1;
        svfull.sem_flg=SEM_UNDO;
        spempty.sem_num=1;//p(empty)
        spempty.sem_op=-1;
        spempty.sem_flg=SEM_UNDO;
        while(1){
            printf("我是生产者 产品:%d 空位:%d\n",semctl(semid,0,GETVAL),semctl(semid,1,GETVAL));
            semop(semid,&spempty,1);
            printf("生产\n");
            semop(semid,&svfull,1);
            printf("我是生产者 产品:%d 空位:%d\n",semctl(semid,0,GETVAL),semctl(semid,1,GETVAL));
            sleep(2);
        }
    }
    return 0;
}