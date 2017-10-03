/************************************************************************
   > File Name:    open.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Wed 28 Sep 2016 11:27:08 AM CST
*******************************************************************/

#include <stdio.h>
#include <errno.h>
#include <string.h>
int main(int argc, const char *argv[])
{
	FILE *fp;
	fp = fopen("./1.txt","a+");
	if(fp == NULL)
	{
//		printf("errno:%s\n",strerror(errno));
		perror("打不开");
		return -1;
	}
	printf("success\n");
	fprintf(fp,"hello world\n");
	if(EOF == fclose(fp))
	{
		perror("close");
		return -1;
	}
	return 0;
}
