#include <stdio.h> // printf(),
#include <stdlib.h> // exit(), EXIT_SUCCESS
#include <semaphore.h> // sem_init()
#include <unistd.h>
#include <mutex>
#include"comm.h"
#include<ctime>


extern sem_t binSem;
extern sem_t binSem2;

extern std::mutex mtxSem; // 保护 sem

void* testThread1(void* arg) {

    int shmid = get_shm();//获取
    char* buf = attach_shm(shmid);//挂接

    while(1) {
         // Wait semaphore
         {

            std::lock_guard<std::mutex> lg(mtxSem);
            sem_wait(&binSem);

         }
            printf("%d-%c\n",1,buf[0]);
            buf[0] = 'B';

            sem_post(&binSem2);
        //  usleep(10);
         

     }

    dttach_shm(buf);
    destory_shm(shmid);
}



void* testThread2(void* arg) {

    int shmid = get_shm();//获取
    char* buf = attach_shm(shmid);//挂接


    while(1) {
         // Wait semaphore
         {

            std::lock_guard<std::mutex> lg(mtxSem);
            sem_wait(&binSem);

         }
            printf("%d-%c\n",2,buf[0]);
            buf[0] = 'B';

            sem_post(&binSem2);
        // usleep(10);

     }

    dttach_shm(buf);
    destory_shm(shmid);
}
