/************************************************************************
   > File Name:    read.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Wed 28 Sep 2016 01:57:37 PM CST
*******************************************************************/

#include <stdio.h>
int main(int argc, const char *argv[])
{
	FILE *fp;
	char buf[64];
	int c;

	fp = fopen("1.txt","r");
	if(fp == NULL)
	{
		perror("fopen");
		return -1;
	}
	while(1)
	{
		c = fgetc(fp);
		if(c == EOF)
		{
			if(0 != feof(fp))
			{
				break;
			}else
			{
				perror("fgetc");
				return -1;
			}
		}
		fputc(c,stdout);
//		fscanf(fp,"%s",buf);
//		fprintf(stdout,"%s\n",buf);
	}

	if(0 != fclose(fp))
	{
		perror("fclose");
		return -1;
	}
	return 0;
}
