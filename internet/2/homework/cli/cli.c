#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>

struct msg
{
	char name[15];
	char buf[128];
	char type;
};

int main(int argc, const char *argv[])
{
	int sockfd;
	
	pid_t pid;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd == -1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in seraddr;
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(50000);
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.252");
	
	struct msg info;
	printf("请输入用户名:");
	info.type = 'L';
	fgets(info.name,sizeof(info.name),stdin);//abc\n\0
	info.name[strlen(info.name) - 1] = '\0';
	sendto(sockfd,&info,sizeof(info),0,(struct sockaddr *)&seraddr,sizeof(seraddr));
	pid = fork();

	if(pid == -1)
	{

	}
	else if(pid == 0)
	{
		while(1)
		{
			printf("请发言:");
			fgets(info.buf,sizeof(info.buf),stdin);
			info.buf[strlen(info.buf) - 1] = '\0';

			if(strncmp(info.buf,"quit",4) == 0)
			{
           		info.type = 'Q';
				sendto(sockfd,&info,sizeof(info),0,(struct sockaddr *)&seraddr,sizeof(seraddr));
			//	kill(getppid(),SIGKILL);
				exit(EXIT_SUCCESS);
			}
			else 
			{
				info.type = 'S';
				sendto(sockfd,&info,sizeof(info),0,(struct sockaddr *)&seraddr,sizeof(seraddr));
			}
		}
	}
	else 
	{
		while(1)
		{
			recvfrom(sockfd,&info,sizeof(info),0,NULL,NULL);
			switch(info.type)
			{
			case 'L':
				printf("%s登录\n",info.name);
				break;
			case 'S':
				printf("%s说%s\n",info.name,info.buf);
				break;
			case 'Q':
				printf("%s退出\n",info.name);
				exit(EXIT_SUCCESS);
		//		break;
			}
		}
	}
	
	return 0;
}
