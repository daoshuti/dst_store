/************************************************************************
   > File Name:    key.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Sun 09 Oct 2016 05:14:40 PM CST
*******************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
int main(int argc, const char *argv[])
{
	key_t key;
	key = ftok("/home",2);
	if(-1 == key)
	{
		perror("ftok");
		return -1;
	}
	printf("key = %x\n",key);
	return 0;
}
