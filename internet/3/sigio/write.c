#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, const char *argv[])
{
	int fd;
	if(mkfifo("./myfifo",0664) == -1)
	{
		if(errno == EEXIST)//有名管道已经存在
		{
			fd = open("./myfifo",O_WRONLY);
		}
		else 
		{
			perror("mkfifo");
			exit(EXIT_FAILURE);
		}
	}
	else //有名管道是当前进程创建的
	{
		fd = open("./myfifo",O_WRONLY);
	}

	char buf[10];
	ssize_t n;
	while(1)
	{
		fgets(buf,sizeof(buf),stdin);	

		write(fd,buf,strlen(buf)+1);
	}
	return 0;
}
