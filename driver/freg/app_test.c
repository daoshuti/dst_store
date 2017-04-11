/*************************************************************************
 @Author: wanghan
 @Created Time : Fri 31 Mar 2017 05:43:44 PM CST
 @File Name: app_test.c
 @Description:
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define FREG_DEVICE_NAME 	"/dev/freg"

int main(int argc, const char *argv[])
{
	int fd = -1;
	int val = 0;
	
	fd = open(FREG_DEVICE_NAME, O_RDWR);
	if(fd == -1)
	{
		printf("Failed to open device %s.\n",FREG_DEVICE_NAME);
		return -1;
	}

	printf("Read original value:\n");
	read(fd, &val, sizeof(val));
	printf("%d.\n\n",val);

	val = 5;
	printf("Write value %d to %s.\n\n", val, FREG_DEVICE_NAME);
	write(fd, &val, sizeof(val));
	
	printf("Read the value again:\n");
	read(fd, &val, sizeof(val));
	printf("%d.\n\n",val);

	close(fd);

	return 0;
}
