/************************************************************************
   > File Name:    pause.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Sun 09 Oct 2016 02:45:56 PM CST
*******************************************************************/

#include <stdio.h>
#include <signal.h>
void fun(int sig)
{
	if(sig == SIGINT)
		printf("want to die\n");
	if(sig == SIGQUIT)
		printf("live 500 years\n");
}
int main(int argc, const char *argv[])
{
	signal(SIGINT,fun);
	signal(SIGQUIT,fun);
	signal(SIGTSTP,SIG_IGN);
	while(1)
	{
		pause();
		printf("happy\n");

	}
	return 0;
}
