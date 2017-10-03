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
			fd = open("./myfifo",O_RDONLY | O_NONBLOCK);
		}
		else 
		{
			perror("mkfifo");
			exit(EXIT_FAILURE);
		}
	}
	else //有名管道是当前进程创建的
	{
		fd = open("./myfifo",O_RDONLY | O_NONBLOCK);
	}

	char buf[10];
	ssize_t n;

	int flag;
	/*以下fcntl的使用方法不是只用于O_NONBLOCK，这种方法使用很广泛*/
	flag = fcntl(0,F_GETFL);//获取文件描述符的原有权限
	flag |= O_NONBLOCK;//添加权限
	
	fcntl(0,F_SETFL,flag);//使设置好的权限生肖

	while(1)
	{
		memset(buf,0,sizeof(buf));
		n = read(fd,buf,sizeof(buf));
		buf[n - 1] = '\0';
		printf("fifo:%s\n",buf);

		memset(buf,0,sizeof(buf));
		n = read(0,buf,sizeof(buf));
		buf[n - 1] = '\0';
		printf("stdin:%s\n",buf);
		sleep(1);

		
	}
	return 0;
}
