/************************************************************************
   > File Name:    signal.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Sun 09 Oct 2016 02:24:53 PM CST
*******************************************************************/

#include <stdio.h>
#include <signal.h>
void handler(int sig)
{
	printf("hello\n");
}
int main(int argc, const char *argv[])
{ 
	signal(SIGINT,handler);
	while(1);
	return 0;
}
