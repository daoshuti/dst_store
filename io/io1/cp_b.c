/************************************************************************
   > File Name:    cp_b.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Wed 28 Sep 2016 03:35:07 PM CST
*******************************************************************/

#include <stdio.h>
#define SIZE 10
int main(int argc, const char *argv[])
{
	FILE *fp1,*fp2;
	char buf[SIZE];
	fp1 = fopen("1.txt","r");
	if(NULL == fp1)
	{
		perror("fopen 1");
		return -1;
	}
	fp2 = fopen("2.txt","w");
	if(NULL == fp2)
	{
		perror("fopen 2");
		return -1;
	}
	while(1)
	{
		if(NULL == fgets(buf,SIZE,fp1))
		{
			if(0 != feof(fp1))
				break;
			else
			{
				perror("fgets");
				return -1;
			}
		}
		fputs(buf,stdout);
		fflush(stdout);
		fputs(buf,fp2);
		sleep(1);
	}
	if(EOF == fclose(fp1))
	{
		perror("fclose 1");
		return -1;
	}
	if(EOF == fclose(fp2))
	{
		perror("fclose 2");
		return -1;
	}
	return 0;
}
