/************************************************************************
   > File Name:    getline.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Wed 28 Sep 2016 04:59:44 PM CST
*******************************************************************/

#include <stdio.h>
#include <string.h>
#define SIZE 1025
int main(int argc, const char *argv[])
{
	FILE *fp;
	int c,line = 0;
	char buf[SIZE];
	fp = fopen("1.txt","r");
	if(fp == NULL)
	{
		perror("fopen");
		return -1;
	}
	while(1)
	{
#if 0
		c = fgetc(fp);
		if(c == EOF)
			break;
		if(c == '\n')
			line ++;
		if(NULL == fgets(buf,SIZE,fp))
			break;
		if(buf[strlen(buf)-1] == '\n')
			line ++;
#endif
		if(NULL == fgets(buf,SIZE,fp))
			break;
		line ++;
	}
	printf("line = %d\n",line);
	return 0;
}
