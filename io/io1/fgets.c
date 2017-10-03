/************************************************************************
   > File Name:    fgets.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Wed 28 Sep 2016 04:10:42 PM CST
*******************************************************************/

#include <stdio.h>
int main(int argc, const char *argv[])
{
	char buf[6];
	while(1)
	{
		fgets(buf,6,stdin);
		printf("%s\n",buf);
	}
	return 0;
}
