/************************************************************************
   > File Name:    homework.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Sat 08 Oct 2016 09:57:29 AM CST
*******************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#define SIZE 64
int a = 10;
int main(int argc, const char *argv[])
{
	int fp1,fp2;
	long len,n,sum = 0;
	pid_t p;
	char buf[SIZE];
	fp1 = open("1.txt",O_RDONLY|O_EXCL);
	if(-1 == fp1)
	{
		perror("open");
		return -1;
	}
	fp2 = open("2.txt",O_WRONLY|O_TRUNC|O_CREAT,0666);
	if(-1 == fp2)
	{
		perror("open 2");
		return -1;
	}
	len = lseek(fp1,0,SEEK_END);
	if(-1 == len)
	{
		perror("lseek");
		return -1;
	}
	len /= 2;
	p = fork();
	if(-1 == p)
	{
		perror("fork");
		return -1;
	}
	if(p > 0)
	{
		a = 20;
		
		if(-1 == close(fp1))
		{
			perror("close 1");
			return -1;
		}
		if(-1 == close(fp2))
		{
			perror("close 2");
			return -1;
		}
		fp1 = open("1.txt",O_RDONLY|O_EXCL);
		if(-1 == fp1)
		{
			perror("open");
			return -1;
		}
		fp2 = open("2.txt",O_WRONLY|O_CREAT,0666);
		if(-1 == fp2)
		{
			perror("open 2");
			return -1;
		}

//		wait(NULL);
		lseek(fp1,0,SEEK_SET);
		lseek(fp2,0,SEEK_SET);
		while(1)
		{
			n = read(fp1,buf,SIZE);
			sum += n;
			if(sum > len)
			{
				write(fp2,buf,n - (sum - len));
				break;
			}
			write(fp2,buf,n);
		}
		printf("a = %d\n",a);
		
	}else
	{
		a = 30;
		lseek(fp1,len,SEEK_SET);
		lseek(fp2,len,SEEK_SET);
		while(1)
		{
			n = read(fp1,buf,SIZE);
			if(n == 0)
				break;
			write(fp2,buf,n);
		}
		printf("a = %d\n",a);
	}
	if(-1 == close(fp1))
	{
		perror("close 1");
		return -1;
	}
	if(-1 == close(fp2))
	{
		perror("close 2");
		return -1;
	}
	return 0;
}
