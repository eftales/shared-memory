#include"comm.h"
static int comm_shm(int size,int shmflg)
{
    key_t key = ftok(PATHNAME,PROJ_ID);//键值
    int shmid = shmget(key,size,shmflg);
    if(shmid < 0)
    {
        perror("shmget");
        return -1;
    }
    return shmid;
}
int create_shm(int size)//共享内存创建
{
    return comm_shm(size,IPC_CREAT|IPC_EXCL|0666);
}
int get_shm()//共享内存获取
{
    return comm_shm(0,IPC_CREAT);
}
int destory_shm(int shmid)//删除
{
    int ret = shmctl(shmid,IPC_RMID,NULL);
    if(ret < 0)
    {
        perror("shmctl");
        return -2;
    }
    return ret;
}
char* attach_shm(int shmid)//挂接
{
    //void* shmat(int shmid,const void*shmaddr,int shmflg)   shmaddr：通常为NULL   shmflg：通常为0
    return (char*)shmat(shmid,NULL,0);
}
int dttach_shm(char* shmaddr)//去挂接
{
    return shmdt(shmaddr);
}
