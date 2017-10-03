/************************************************************************
   > File Name:    size.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Wed 28 Sep 2016 05:16:13 PM CST
*******************************************************************/

#include <stdio.h>
int main(int argc, const char *argv[])
{
	long size;
	FILE *fp;
	fp = fopen("1.txt","r+");
	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	printf("size = %ld\n",size);
	return 0;
}
