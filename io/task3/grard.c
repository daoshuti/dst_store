/************************************************************************
   > File Name:    grard.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Sun 09 Oct 2016 09:50:53 AM CST
*******************************************************************/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, const char *argv[])
{
	pid_t p;
	int fp;
	time_t t;
	char buf[64];
	/*创建子进程，父进程退出*/
	p = fork();
	if(p > 0)
		exit(0);
	/*切换工作的文件目录*/
	chdir("/");
	/*更改文件权限掩码*/
	umask(0);
	/*创建会话组*/
	setsid();
	/*关闭多余的文件描述符*/
	for(fp = 0;fp < getdtablesize();fp ++)
		close(fp);
	/*开始工作*/
	fp = open("log",O_WRONLY|O_CREAT|O_APPEND,0666);
	while(1)
	{
		t = time(NULL);
		sprintf(buf,"%s",ctime(&t));
		write(fp,buf,strlen(buf));
		sleep(1);
	}
	return 0;
}
