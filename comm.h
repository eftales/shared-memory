#ifndef _COMM_H_
#define _COMM_H_
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<errno.h>
#define PATHNAME "."
#define PROJ_ID 0x6666

int create_shm(int size);//创建共享内存
int get_shm();//获取共享内存
int destory_shm(int shmid);//删除共享内存
char* attach_shm(int shmid);//共享内存挂接
int dttach_shm(char* shmaddr);//共享内存去挂接
#endif
