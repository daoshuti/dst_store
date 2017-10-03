/************************************************************************
   > File Name:    stat.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Thu 29 Sep 2016 03:29:28 PM CST
*******************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
int main(int argc, const char *argv[])
{
	struct stat buf; 
	stat(argv[1],&buf);
	if(S_ISREG(buf.st_mode))
		printf("-");
	if(S_ISDIR(buf.st_mode))
		printf("d");
	if(S_ISLNK(buf.st_mode))
		printf("l");


	if(S_IRUSR & buf.st_mode)
		printf("r");
	else
		printf("-");
	if(S_IWUSR & buf.st_mode)
		printf("w");
	else
		printf("-");
	if(S_IXUSR & buf.st_mode)
		printf("x");
	else
		printf("-");


	if(S_IRGRP & buf.st_mode)
		printf("r");
	else
		printf("-");
	if(S_IWGRP & buf.st_mode)
		printf("w");
	else
		printf("-");
	if(S_IXGRP & buf.st_mode)
		printf("x");
	else
		printf("-");


	if(S_IROTH & buf.st_mode)
		printf("r");
	else
		printf("-");
	if(S_IWOTH & buf.st_mode)
		printf("w");
	else
		printf("-");
	if(S_IXOTH & buf.st_mode)
		printf("x");
	else
		printf("-");

	printf(" %u ",buf.st_nlink);

	printf("%s ",getpwuid(buf.st_uid)->pw_name);
	printf("%s ",getgrgid(buf.st_gid)->gr_name);

	printf("%ld ",buf.st_size);
	printf("%s",ctime(&buf.st_mtime));
	return 0;
}
