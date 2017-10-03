/************************************************************************
   > File Name:    fseek.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Thu 29 Sep 2016 09:42:47 AM CST
*******************************************************************/

#include <stdio.h>
int main(int argc, const char *argv[])
{
	FILE *fp;
	fp = fopen("test.txt","r+");
	fseek(fp,10,SEEK_END);
	fputc('\0',fp);
	fputc('a',fp);
	return 0;
}
