/************************************************************************
   > File Name:    mutex.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Sat 08 Oct 2016 04:44:01 PM CST
*******************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
int a,b,c;
sem_t sem;
pthread_mutex_t mutex;
void *fun1(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
//		sem_wait(&sem);
		a++;
		b = a;
		c = a;
		pthread_mutex_unlock(&mutex);
//		sem_post(&sem);
	}
}
void *fun2(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
//		sem_wait(&sem);
		if(b != c)
			printf("a = %d,b = %d,c = %d\n",a,b,c);
		pthread_mutex_unlock(&mutex);
//		sem_post(&sem);
	}
}
int main(int argc, const char *argv[])
{
	pthread_t pthid1,pthid2;
	sem_init(&sem,0,1);
	pthread_mutex_init(&mutex,NULL);
	pthread_create(&pthid1,NULL,fun1,NULL);
	pthread_create(&pthid2,NULL,fun2,NULL);
	pthread_join(pthid1,NULL);
	pthread_join(pthid2,NULL);
	return 0;
}
