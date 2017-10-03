/************************************************************************
   > File Name:    kill.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Sun 09 Oct 2016 02:34:20 PM CST
*******************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
int main(int argc, const char *argv[])
{
	pid_t p;
	p = fork();
	if(-1 == p)
	{
		perror("fork");
		return -1;
	}
	if(p == 0)
	{
		alarm(2);
		while(1)
		{
			printf("happy\n");
			usleep(100000);
		}
	}else
	{
		printf("I am the father\n");
		sleep(1);
//		kill(p,SIGALRM);
		printf("bye\n");
	}
	return 0;
}
