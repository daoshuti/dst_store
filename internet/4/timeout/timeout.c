#include<stdio.h>
#include<signal.h>
#include<string.h>

void func(int signo)
{
	if(signo == SIGALRM)
	{
		printf("timeout\n");
	}
}

int main(int argc, const char *argv[])
{

	char buf[10];
	int n;
#if 1
	struct sigaction act;

	act.sa_handler = func;
	act.sa_flags = 0;
//	act.sa_flags |= SA_RESTART;//因为read出现超时后，会重新返回到read函数去读取数据，但是alarm函数没有进行第二次设置，所以不会再出现超时
	act.sa_flags &= ~SA_RESTART;//一旦出现超时，则会跳过read函数
	sigaction(SIGALRM,&act,NULL);
#endif 

//	signal(SIGALRM,func);相当于sigaction使用了sa_flags |= SA_RESTART;
	while(1)
	{
		printf("start\n");
		alarm(5);
		
		memset(buf,0,sizeof(buf));
		if((n = read(0,buf,sizeof(buf))) == -1)
		{
			printf("error\n");
		}
		printf("n = %d\n",n);
		printf("stdin:%s\n",buf);

	}
	return 0;
}
