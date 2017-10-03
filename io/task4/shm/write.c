/************************************************************************
   > File Name:    write.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Mon 10 Oct 2016 11:09:16 AM CST
*******************************************************************/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
typedef struct shmbuf
{
	char buf[64];
}SHM;
int main(int argc, const char *argv[])
{
	SHM *shmb;
	key_t key;
	int shmid;
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
	printf("shmid = %d\n",shmid);
	if(-1 == *(int *)(shmb = (SHM *)shmat(shmid,NULL,0)))
	{
		perror("shmat");
		return -1;
	}
	while(1)
	{
		//memset(shmb->buf,'\0',64);
		fgets(shmb->buf,64,stdin);
		if(0 == strncmp("quit",shmb->buf,4))
			break;
	}

	return 0;
}
