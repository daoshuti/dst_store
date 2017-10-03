/************************************************************************
   > File Name:    cp.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Thu 29 Sep 2016 11:42:53 AM CST
*******************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define SIZE 16
int main(int argc, const char *argv[])
{
	int fp1,fp2,n;
	char buf[SIZE];
	if(argc != 3)
	{
		printf("error\n");
		return -1;
	}
	if(-1 ==(fp1 = open(argv[1],O_RDONLY|O_EXCL)))
	{
		perror("open1");
		return -1;
	}
	if(-1 ==(fp2 = open(argv[2],O_WRONLY|O_TRUNC|O_CREAT,0666)))
	{
		perror("open2");
		return -1;
	}
	while(1)
	{
		n = read(fp1,buf,SIZE);
		if(n  == 0)
			break;
		if(n == -1)
		{
			perror("read");
			return -1;
		}
		printf("%s\n",buf);
		write(fp2,buf,n);
		sleep(1);
	}
	if(-1 == close(fp1))
	{
		perror("close1");
		return -1;
	}
	if(-1 == close(fp2))
	{
		perror("close2");
		return -1;
	}
	return 0;
}
