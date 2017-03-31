/*************************************************************************
 @Author: wanghan
 @Created Time : Thu 30 Mar 2017 07:01:58 PM CST
 @File Name: point.c
 @Description:
 ************************************************************************/
#include<stdio.h>

int main(int argc, const char *argv[])
{
	unsigned int a = 10;
	unsigned int *p = &a;
	printf("p = %p\n",p);
	printf("p = %u\n",p);
	printf("p = %x\n",p);
	printf("*p = %u\n",*p);
	return 0;
}
