#include <stdio.h>


int main(int argc, const char *argv[])
{
	//1 野指针
	//	char *p;

	//printf("%s\n",p);
	
	//2 0地址
	//char *p =NULL;

	//*p='a';  
	//0地址  NULL  只能用来作为比较，而不能用来访问内容，或者复制  
	

	//3 
	char* s1="abcdefg";//本质  字符串常量  常量无法被改变
	char* s2="abcdefg";//编译器优化   只需要一个位置存储相同的字符串常量

	if(s1==s2)
	{
		printf("is same\n");
	}
	else
		printf("not the same\n");

	//	s1[1]='a'; 常量不能被修改


	//4
	int shuzu[10];

	//	shuzu++;
	//数组名是  地址常量  无法修改
	//

	//5
	//数组越界
	int i=0;

	while(++i)
	{
		printf("shuzu[%d]=%d\n",i,shuzu[i]);
	
	}



	return 0;
}
