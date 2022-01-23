#include <func.h>

int main(){
    int shmid;
    shmid=shmget(IPC_PRIVATE,4096,IPC_CREAT|0600);//(共享内存段相关联关键字(有直接返回该内存段标识;无则创建),大小,创建|权限)
    //key值:1.ftok函数产生;2.IPC_PRIVATE创建一个只属于创建进程的key;3.写死
    ERROR_CHECK(shmid,-1,"shmget");
    char* p=shmat(shmid,NULL,0);//连接(共享存储标识,连接地址(由系统决定,一般未知填NULL),组位标识通常为0)
    ERROR_CHECK(p,(char*)-1,"shmat");//shmat失败返回(char*)-1
    memset(p,0,4096);
    if(!fork()){
        strcpy(p,"how are you");
        int ret=shmdt(p);//写完解除连接,当未解除连接的情况下删除共享内存段会使其标记删除
        ERROR_CHECK(ret,-1,"shmdt");
    }else{
        sleep(2);
        printf("shared memery:%s\n",p);
        int ret=shmdt(p);
        ERROR_CHECK(ret,-1,"shmdt");
        shmctl(shmid,IPC_RMID,NULL);//共享内存控制:id，操作(IPC_RMID 删除),共享存储信息结构体数据
        wait(NULL);
    }
    return 0;
}