/************************************************************************
   > File Name:    bus.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Sun 09 Oct 2016 04:05:24 PM CST
*******************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
pid_t pid;
void ticket(int sig)
{
	switch(sig)
	{
		case SIGINT:
			kill(getppid(),SIGUSR1);
			break;
		case SIGQUIT:
			kill(getppid(),SIGUSR2);
			break;
		case SIGUSR1:
			printf("please get off\n");
			kill(getppid(),SIGKILL);
			raise(SIGKILL);
			break;
	}
}
void driver(int sig)
{
	switch(sig)
	{
	case SIGUSR1:
		printf("let's gogogo\n");
		break;
	case SIGUSR2:
		printf("stop the bus\n");
		break;
	case SIGTSTP:
		kill(pid,SIGUSR1);
		break;
	}
}
int main(int argc, const char *argv[])
{
	pid = fork();
	if(-1 == pid)
	{
		perror("fork");
		return -1;
	}
	if(pid == 0)
	{
		signal(SIGINT,ticket);
		signal(SIGQUIT,ticket);
		signal(SIGUSR1,ticket);
		signal(SIGTSTP,SIG_IGN);
	}else
	{
		signal(SIGINT,SIG_IGN);
		signal(SIGQUIT,SIG_IGN);
		signal(SIGUSR1,driver);
		signal(SIGUSR2,driver);
		signal(SIGTSTP,driver);
	}
	while(1)
		pause();
	return 0;
}
