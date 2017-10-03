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
int a,b,c;
pthread_mutex_t mutex;
pthread_cond_t cond;
void *thread_fun1(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		a ++;
		printf("a = %d\n",a);
		if(a == 100000)
			pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
}
void *thread_fun3(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond,&mutex);
		c = a;
		printf("c = %d\n",c);
		pthread_cancel(pth_id1);
		pthread_cancel(pth_id2);
		pthread_exit(NULL);
		pthread_mutex_unlock(&mutex);
	}
}
int main(int argc, const char *argv[])
{
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	if(0 != pthread_create(&pth_id1,NULL,thread_fun1,NULL))
	{
		perror("pthread_create1");
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
	if(0 != pthread_join(pth_id3,NULL))
	{
		perror("pthread_join3");
		return -1;
	}
	//	sleep(1);
	printf("morning\n");
	return 0;
}
