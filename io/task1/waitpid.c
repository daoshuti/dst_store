/************************************************************************
   > File Name:    wait.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Fri 30 Sep 2016 04:02:08 PM CST
*******************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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
		printf("I am runing\n");
		sleep(1);
		printf("good\n");
	}else
	{
		printf("I am waiting\n");
		waitpid(p,NULL,WNOHANG);
		printf("bye\n");

	}
	return 0;
}
