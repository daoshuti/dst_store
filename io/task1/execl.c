/************************************************************************
   > File Name:    execl.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Fri 30 Sep 2016 03:23:39 PM CST
*******************************************************************/

#include <stdio.h>
#include <unistd.h>
int main(int argc, const char *argv[])
{
	execl("/bin/ls","ls","-l",NULL);
	return 0;
}
