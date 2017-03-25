#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, const char *argv[])
{
	int count = 0;
	char buf[32] = {0};
	int fd;
	int mask=umask(0);
	printf("mask=%o\n",mask);
	fd = open("./while.log",O_RDWR|O_CREAT);
	if(fd < 0)
	{
		printf("open fail\n");
		return -1;
	}
	while(1)
	{
		sleep(1);
		memset(buf,'\0',sizeof(buf));
		sprintf(buf,"count = %d\n",count++);
		write(fd,buf,strlen(buf));
		fsync(fd);
//	printf("%s",buf);
//		if(count > 5)
//			break;
	}
	return 0;
}
