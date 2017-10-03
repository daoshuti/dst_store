/************************************************************************
   > File Name:    fifo.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Sun 09 Oct 2016 11:02:31 AM CST
*******************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
int main(int argc, const char *argv[])
{
	int fd;
	char buf[64];
	if(0 != mkfifo("fifo",0666))
	{
		if(errno == EEXIST)
		{
			if(-1 ==(fd = open("fifo",O_WRONLY)))
			{
				perror("open");
				return -1;
			}
		}else
		{
			perror("mkfifo");
			return -1;
		}
	}
	printf("fd = %d\n",fd);
	while(1)
	{
		//read();//从文件读
		fgets(buf,64,stdin);
		write(fd,buf,64);
		if(0 ==strncmp("quit",buf,4))
			break;
	}
	if(-1 == close(fd))
	{
		perror("close");
		return -1;
	}
	return 0;
}
