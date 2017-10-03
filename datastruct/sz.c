#include <stdio.h>

int main(int argc, const char *argv[])
{
	int stack[64];
	int top = -1;
	int a,b;
	printf("请输入进制:");
	scanf("%d",&a);
	printf("请输入数值:");
	scanf("%d",&b);
	while(b){
		stack[++top]=b%a;
		b=b/a;
	}
	while(top>=0)
		printf("%d",stack[top--]);
	printf("\n");
	return 0;
}
