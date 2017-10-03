/************************************************************************
   > File Name:    lseek.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Thu 29 Sep 2016 01:31:10 PM CST
*******************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, const char *argv[])
{
	int fp;
	long len;
	fp = open("1.txt",O_RDONLY|O_EXCL);
	if(fp == -1)
	{
		perror("open");
		return -1;
	}
	len = lseek(fp,0,SEEK_END);
	printf("len = %ld\n",len);
	return 0;
}
