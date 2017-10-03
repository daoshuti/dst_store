/************************************************************************
   > File Name:    io.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Sat 08 Oct 2016 04:11:44 PM CST
*******************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define SIZE 64
sem_t sem1,sem2;
char buf[SIZE];
void *fun1(void *arg)
{
	while(1)
	{
	//	sem_wait(&sem1);
		fgets(buf,SIZE,stdin);
		sem_post(&sem2);
		if(strncmp("quit",buf,4) == 0)
			break;
	}
}
void *fun2(void *arg)
{
	while(1)
	{
		sem_wait(&sem2);
		fputs(buf,stdout);
		if(strncmp("quit",buf,4) == 0)
			break;
	//	sem_post(&sem1);
	}
}
int main(int argc, const char *argv[])
{
	pthread_t pth_id1,pth_id2;
	if(0 != pthread_create(&pth_id1,NULL,fun1,NULL))
	{
		perror("pthread_create 1");
		return -1;
	}
	if(0 != pthread_create(&pth_id2,NULL,fun2,NULL))
	{
		perror("pthread_create 2");
		return -1;
	}
//	if(0 != sem_init(&sem1,0,1))
//	{
//		perror("sem_init 1");
//		return -1;
//	}
	if(0 != sem_init(&sem2,0,0))
	{
		perror("sem_init 2");
		return -1;
	}
	if(0 != pthread_join(pth_id1,NULL))
	{
		perror("pthread_join 1");
		return -1;
	}
	if(0 != pthread_join(pth_id2,NULL))
	{
		perror("pthread_join 2");
		return -1;
	}
	printf("bye\n");
	return 0;
}
