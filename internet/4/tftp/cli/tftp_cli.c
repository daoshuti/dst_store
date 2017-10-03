#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

#define SEARCH 1
#define DOWN 2

#define FALSE 3
#define TRUE 4
typedef struct tftp
{
	int type;
	int flag;
	char buf[128];
	char fname[15];
}tftp_t;

void serach_file(tftp_t info,int sockfd)
{
	int count = 0;
	info.type = SEARCH;
	send(sockfd,&info,sizeof(info),0);
	recv(sockfd,&info,sizeof(info),0);

//	printf("%s\n",info.buf);
	int i;

	for(i = 0;i < strlen(info.buf);i ++)
	{
		if(info.buf[i] == ' ')
		{
			count ++;
			if(count % 5 == 0)
				info.buf[i] = '\n';
		}
	}
	printf("%s",info.buf);
	printf("\n");
}

void tftp_down(tftp_t info,int sockfd)
{
	info.type = DOWN;
	printf("请输入要下载的文件名:");
	fgets(info.fname,sizeof(info.fname),stdin);
	info.fname[strlen(info.fname) - 1] = '\0';

	send(sockfd,&info,sizeof(info),0);
	recv(sockfd,&info,sizeof(info),0);

	if(info.flag == FALSE)
	{
		printf("服务器文件打开失败\n");
		return ;
	}	
	else 
		printf("服务器文件打开成功\n");

	FILE *fp;
	int len;
	fp = fopen(info.fname,"w");
	if(fp == NULL)
	{
		printf("客户端打开文件失败\n");
		return;
	}

	while(1)
	{
		len = recv(sockfd,info.buf,sizeof(info.buf),0);
		
		printf("cli:%s\n",info.buf);
		fwrite(info.buf,1,len,fp);
		if(len < sizeof(info.buf))
			break;

	}
	printf("下载成功\n");
	fclose(fp);
	
}

int main(int argc, const char *argv[])
{
	int sockfd; 
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{

	}
	struct sockaddr_in seraddr;

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(50000);
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.252");

	
	connect(sockfd,(const struct sockaddr *)&seraddr,sizeof(seraddr));
	
	char choose[10];
	int choice;
	tftp_t info;
	while(1)
	{
		printf("*1.查询 2.下载\n");
		fgets(choose,sizeof(choose),stdin);
		choice = choose[0] - '0';
		
		switch(choice)
		{
		case 1:
			serach_file(info,sockfd);
			break;
		case 2:
			tftp_down(info,sockfd);
			break;
	//	case 3:
	//		tftp_up();
	//		break;
		}

	}
	close(sockfd);
	return 0;
}
