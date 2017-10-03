/************************************************************************
   > File Name:    vip.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Fri 30 Sep 2016 02:37:30 PM CST
*******************************************************************/

#include <stdio.h>
#include <unistd.h>
int main(int argc, const char *argv[])
{
	pid_t p1,p2;
	p1 = fork();
	p2 = fork();
	printf("p1 = %d,p2 = %d\n",p1,p2);
	return 0;
}
