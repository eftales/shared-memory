#include <stdio.h> // printf(),
#include <stdlib.h> // exit(), EXIT_SUCCESS
#include <pthread.h> // pthread_create(), pthread_join()
#include <semaphore.h> // sem_init()
#include "signal_handler.h"
#include <unistd.h>
#include"comm.h"

sem_t binSem;
sem_t binSem2;

#include <mutex>
std::mutex mtxSem; // 保护 sem

int main() {
     system("ipcrm -a"); // 删除上一次运行时创建的共享内存段

     // Result for System call
    int res = 0;

     // Initialize semaphore
     res = sem_init(&binSem, 0, 0);
    if (res) {
         printf("Semaphore initialization failed!!\n");
         exit(EXIT_FAILURE);
     }

     res = sem_init(&binSem2, 0, 0);
    if (res) {
         printf("Semaphore initialization failed!!\n");
         exit(EXIT_FAILURE);
     }

     // shared memory
     int shmid = create_shm(4096);//创建
     if (shmid == -1){
          destory_shm(shmid);
     }
     char* buf = attach_shm(shmid);//挂接





     // Create thread
     pthread_t th1;
     res = pthread_create(&th1, NULL, testThread1, NULL);
    if (res) {
         printf("Thread creation failed!!\n");
         exit(EXIT_FAILURE);
     }


     pthread_t th2;
     res = pthread_create(&th2, NULL, testThread2, NULL);
    if (res) {
         printf("Thread creation failed!!\n");
         exit(EXIT_FAILURE);
     }

    while(1) {
         // Post semaphore
         sem_post(&binSem);
         
         buf[0] = 'A';
         sem_wait(&binSem2);
         printf("%c\n",buf[0]);

     }

     // Wait for thread synchronization
//      void *threadResult;
//      res = pthread_join(th1, &threadResult);
//     if (res) {
//          printf("Thread join failed!!\n");
//          exit(EXIT_FAILURE);
//      }


     dttach_shm(buf);
     destory_shm(shmid);
     return 0;

     exit(EXIT_SUCCESS);
}



