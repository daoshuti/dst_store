/*************************************************************************
 @Author: wanghan
 @Created Time : Sat 01 Apr 2017 11:31:09 PM CST
 @File Name: builtin_return_address.c
 @Description:
 ************************************************************************/
#include <stdio.h>

//typedef void (*p)(int) pfun_t;

void *fun1(int flag){
	void *p = __builtin_return_address(0);
	if(flag) printf("I am fun1.\n");
	else printf("I am fun1. call me.\n");
	return p;
}

void *fun2(int flag){
	void *p = __builtin_return_address(0);
	if(flag) printf("I am fun2.\n");
	else printf("I am fun2. call me.\n");
	return p;
}

void *rfun1(void){
	return fun1(0);
}

void *rfun2(void){
	return fun2(0);
}

int main(int argc, const char *argv[])
{
#if 0
	void *pfun1 = (void *)fun1;
	void *pfun2 = (void *)fun2;
	void *prfun1 = (void *)rfun1;
	void *prfun2 = (void *)rfun2;
#endif
	printf("pfun1 = %p\n",fun1);
	printf("pfun2 = %p\n",fun2);
	printf("prfun1 = %p\n",rfun1);
	printf("prfun2 = %p\n",rfun2);
	printf("prfun1_return = %p\n",rfun1());
	printf("prfun2_return = %p\n",rfun2());
	return 0;
}
