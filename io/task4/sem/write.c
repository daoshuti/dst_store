/************************************************************************
   > File Name:    write.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Mon 10 Oct 2016 11:09:16 AM CST
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
union semun {//初始化val要使用的共用体
	int		val;	/* Value for SETVAL */
	struct semid_ds *buf;	/* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;	/* Array for GETALL, SETALL */
	struct seminfo  *__buf;	/* Buffer for IPC_INFO
							   (Linux-specific) */
};
typedef struct shmbuf
{
	char buf[64];
}SHM;
void seminit(int semid)//初始化信号灯
{
	union semun sem;
	sem.val = 1;//初始化的资源数目
	if(-1 == semctl(semid,0,SETVAL,sem))//设置第0个信号灯的初值
	{
		perror("semctl");
		exit(EXIT_FAILURE);
	}
}
void sem_p(int semid)//P操作
{
	struct sembuf buf={
		0,-1,SEM_UNDO//第0个信号，资源数目减1，自动设置
	};
	if(-1 == semop(semid,&buf,1))//将结构体内容设置成功
	{
		perror("semopp");
		exit(EXIT_FAILURE);
	}
}
void sem_v(int semid)//V操作
{
	struct sembuf buf={
		0,1,SEM_UNDO//第0个信号，资源数目加1，自动设置
	};
	if(-1 == semop(semid,&buf,1))
	{
		perror("semopv");
		exit(EXIT_FAILURE);
	}
}
int main(int argc, const char *argv[])
{
	SHM *shmb;
	key_t key;
	int shmid,semid;
	key = ftok("..",250);
	if(-1 == key)
	{
		perror("ftok");
		return -1;
	}
	shmid = shmget(key,sizeof(SHM),IPC_CREAT|IPC_EXCL|0666);
	if(-1 == shmid)
	{
		if(errno == EEXIST)
		{
			shmid = shmget(key,sizeof(SHM),0);
		}else
		{
			perror("shmget");
			return -1;
		}
	}
	semid = semget(key,1,IPC_CREAT|IPC_EXCL|0666);
	if(-1 == semid)
	{
		if(errno == EEXIST)
		{
			semid = semget(key,1,0);
		}else
		{
			perror("semget");
			return -1;
		}
	}
	printf("shmid = %d\n",shmid);
	printf("semid = %d\n",semid);
	if(-1 == *(int *)(shmb = (SHM *)shmat(shmid,NULL,0)))
	{
		perror("shmat");
		return -1;
	}
	seminit(semid);//使用之前一定要初始化。
	while(1)
	{
		sem_p(semid);
		//memset(shmb->buf,'\0',64);
		fgets(shmb->buf,64,stdin);
		sem_v(semid);
		if(0 == strncmp("quit",shmb->buf,4))
			break;
	}
	return 0;
}
