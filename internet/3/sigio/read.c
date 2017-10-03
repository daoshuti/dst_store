#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>

int fd;
void func(int signo)
{
	char buf[128];
	int n;
	if(signo == SIGIO)
	{
		n = read(fd,buf,sizeof(buf));
		buf[n - 1] = '\0';

		printf("read fifo:%s\n",buf);
	}
}
int main(int argc, const char *argv[])
{
	if(mkfifo("./myfifo",0664) == -1)
	{
		if(errno == EEXIST)//有名管道已经存在
		{
			fd = open("./myfifo",O_RDONLY);
		}
		else 
		{
			perror("mkfifo");
			exit(EXIT_FAILURE);
		}
	}
	else //有名管道是当前进程创建的
	{
		fd = open("./myfifo",O_RDONLY);
	}
	signal(SIGIO,func);
	char buf[10];
	ssize_t n;

	int flag;
	flag = fcntl(fd,F_GETFL);//获取文件描述符的原有权限
	flag |= O_ASYNC;//添加异步权限
	
	fcntl(fd,F_SETFL,flag);//使设置好的权限生肖
	
	fcntl(fd,F_SETOWN,getpid());//给当前进程注册信号
	
	while(1)
	{
		printf("end\n");
		sleep(1);
	}
	return 0;
}
