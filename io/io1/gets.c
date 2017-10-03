/************************************************************************
   > File Name:    gets.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Wed 28 Sep 2016 03:18:35 PM CST
*******************************************************************/

#include <stdio.h>
int main(int argc, const char *argv[])
{
	char buf[6];
	gets(buf);
	printf("%s\n",buf);
	return 0;
}
