/************************************************************************
   > File Name:    pthread.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Sat 08 Oct 2016 11:35:56 AM CST
*******************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
pthread_t pth_id1,pth_id2,pth_id3;
sem_t sem1,sem2,sem3;
int a,b,c;
void *thread_fun1(void *arg)
{
	while(1)
	{
		sem_wait(&sem1);//sem1的value -1变成0,下一次阻塞等待变成1
		a ++;
		printf("a = %d\n",a);
		sem_post(&sem2);
	}
}
void *thread_fun2(void *arg)
{
	while(1)
	{
		sem_wait(&sem2);
		b = a;
		printf("b = %d\n",b);
		sem_post(&sem3);
	}
}
void *thread_fun3(void *arg)
{
	while(1)
	{
		sem_wait(&sem3);
		c = b;
		printf("c = %d\n",c);
		if(c == 10000)
		{
			pthread_cancel(pth_id1);
			pthread_cancel(pth_id2);
			pthread_exit(NULL);
		}
		sem_post(&sem1);
	}
}
int main(int argc, const char *argv[])
{
	if(0 != sem_init(&sem1,0,1))
	{
		perror("sem_init 1");
		return -1;
	}
	if(0 != sem_init(&sem2,0,0))
	{
		perror("sem_init 2");
		return -1;
	}
	if(0 != sem_init(&sem3,0,0))
	{
		perror("sem_init 3");
		return -1;
	}
	if(0 != pthread_create(&pth_id1,NULL,thread_fun1,NULL))
	{
		perror("pthread_create1");
		return -1;
	}
	if(0 != pthread_create(&pth_id2,NULL,thread_fun2,NULL))
	{
		perror("pthread_create2");
		return -1;
	}
	if(0 != pthread_create(&pth_id3,NULL,thread_fun3,NULL))
	{
		perror("pthread_create2");
		return -1;
	}
	if(0 != pthread_join(pth_id1,NULL))
	{
		perror("pthread_join1");
		return -1;
	}
	if(0 != pthread_join(pth_id2,NULL))
	{
		perror("pthread_join2");
		return -1;
	}
	if(0 != pthread_join(pth_id3,NULL))
	{
		perror("pthread_join3");
		return -1;
	}
	//	sleep(1);
	printf("morning\n");
	return 0;
}
