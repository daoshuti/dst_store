/************************************************************************
   > File Name:    homework.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Thu 29 Sep 2016 09:02:06 AM CST
*******************************************************************/

#include <stdio.h>
#include <time.h>
int main(int argc, const char *argv[])
{
	FILE *fp;
	int c,line = 1;
	time_t t;
	struct tm *st;

	fp = fopen("test.txt","a+");
	if(fp == NULL)
	{
		perror("fopen");
		return -1;
	}
	while((c = fgetc(fp)) != EOF)
	{
		if(c == '\n')
			line ++;
	}
	while(1)
	{
		t = time(NULL);
		st = localtime(&t);
		fprintf(fp,"%d,%d-%d-%d %d:%d:%d\n",line ++,st->tm_year + 1900,
				st->tm_mon + 1,st ->tm_mday,st->tm_hour,st->tm_min,st->tm_sec);
		fflush(fp);
		sleep(1);
	}
	return 0;
}
