/************************************************************************
   > File Name:    open.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Thu 29 Sep 2016 11:05:40 AM CST
*******************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, const char *argv[])
{
	int fp,n;
	char buf[16];
	fp = open("1.txt",O_RDONLY|O_EXCL);
	if(-1 == fp)
	{
		perror("open");
		return -1;
	}
//	memset(buf,'\0',16);
	while(1)
	{
		n = read(fp,buf,16);
		if(n == -1)
		{
			perror("read");
			return -1;
		}
		if(n == 0)
			break;
//		printf("%s\n",buf);
		write(1,buf,n);
	}
	return 0;
}
