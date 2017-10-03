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
union semun {
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
void seminit(int semid)
{
	union semun sem;
	sem.val = 0;
	if(-1 == semctl(semid,0,SETVAL,sem))
	{
		perror("semctl");
		exit(EXIT_FAILURE);
	}
}
void sem_p(int semid)
{
	struct sembuf buf={
		0,-1,SEM_UNDO
	};
	if(-1 == semop(semid,&buf,1))
	{
		perror("semopp");
		exit(EXIT_FAILURE);
	}
}
void sem_v(int semid)
{
	struct sembuf buf={
		0,1,SEM_UNDO
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
	seminit(semid);
	while(1)
	{
		sem_p(semid);
		//fgets(shmb->buf,64,stdin);
		printf("%s",shmb->buf);
		if(0 == strncmp("quit",shmb->buf,4))
			break;
		memset(shmb->buf,'\0',64);
		sem_v(semid);
	}
	if(0 != shmctl(shmid,IPC_RMID,NULL))
	{
		perror("shmctl");
		return -1;
	}
	if(0 != semctl(semid,0,IPC_RMID,NULL))
	{
		perror("semctl");
		return -1;
	}

	return 0;
}
