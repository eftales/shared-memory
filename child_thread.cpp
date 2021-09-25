#include <stdio.h> // printf(),
#include <stdlib.h> // exit(), EXIT_SUCCESS
#include <semaphore.h> // sem_init()
#include <unistd.h>
#include"comm.h"

extern sem_t binSem;
extern sem_t binSem2;


void* helloWorld(void* arg) {

    int shmid = get_shm();//获取
    char* buf = attach_shm(shmid);//挂接

    while(1) {
         // Wait semaphore
         sem_wait(&binSem);
         printf("%c\n",buf[0]);
         buf[0] = 'B';

         sem_post(&binSem2);
     }

    dttach_shm(buf);
    destory_shm(shmid);
}
