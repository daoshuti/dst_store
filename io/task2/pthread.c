/************************************************************************
   > File Name:    pthread.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Sat 08 Oct 2016 11:35:56 AM CST
*******************************************************************/

#include <stdio.h>
#include <pthread.h>
int a,b,c;
void *thread_fun1(void *arg)
{
	while(1)
	{
		a ++;
		printf("a = %d\n",a);
	}
}
void *thread_fun2(void *arg)
{
	while(1)
	{
		b = a;
		printf("b = %d\n",b);
	}
}
void *thread_fun3(void *arg)
{
	while(1)
	{
		c = b;
		printf("c = %d\n",c);
	}
}
int main(int argc, const char *argv[])
{
	pthread_t pth_id1,pth_id2,pth_id3;
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
