/************************************************************************
   > File Name:    fork.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Fri 30 Sep 2016 01:55:17 PM CST
*******************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(int argc, const char *argv[])
{
	pid_t p;
	printf("today\n");
	p = fork();
	if(p == -1)
	{
		perror("fork");
		return -1;
	}
	if(p == 0)
	{
		printf("I am the child,my pid = %d,my father is %d\n",getpid(),getppid());
	}else
	{
		printf("I am the father,my pid = %d,my child is %d\n",getpid(),p);
		wait(NULL);
		//sleep(1);
	}
	return 0;
}
