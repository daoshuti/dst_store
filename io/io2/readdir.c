/************************************************************************
   > File Name:    readdir.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Thu 29 Sep 2016 03:54:22 PM CST
*******************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
int main(int argc, const char *argv[])
{
	DIR *fp;
	struct dirent *dir;
	fp = opendir(".");
	while(1)
	{
		dir = readdir(fp);
		if(dir == NULL)
			break;
		printf("%s\t",dir->d_name);

	}
	printf("\n");
	return 0;
}
