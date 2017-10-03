/************************************************************************
   > File Name:    grand.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Fri 30 Sep 2016 02:33:29 PM CST
*******************************************************************/

#include <stdio.h>
#include <unistd.h>
int main(int argc, const char *argv[])
{
	pid_t p;
	p = fork();
	if(-1 == p)
	{
		perror("fork");
		return -1;
	}
	if(p > 0)//父进程
	{
		printf("I am the father\n");
		sleep(1);
	}else//子进程
	{
		printf("I am the child\n");
		p = fork();
		if(p == 0)
			printf("I am the grandson\n");

	}
	
	return 0;
}
