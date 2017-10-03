#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<string.h>

int main(int argc, const char *argv[])
{
	int sockfd;

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

	if(bind(sockfd,(const struct sockaddr *)&seraddr,sizeof(seraddr)) == -1)
	{

	}

	struct sockaddr_in cliaddr;
	char buf[128];
	int clilen = sizeof(cliaddr);
	
	int recvlen;
	int readlen;
	
	int maxfd = sockfd;
	fd_set readfds;
	
	FD_ZERO(&readfds);//将readfds清0
	int select_n;
	int i;
	while(1)
	{
		FD_SET(0,&readfds);
		FD_SET(sockfd,&readfds);
		printf("first\n");
		select_n = select(maxfd + 1,&readfds,NULL,NULL,NULL);
		printf("second\n");

		if(select_n == -1)
		{
			perror("select");
			return -1;
		}
		printf("select_n = %d\n",select_n);

		//判断出哪个文件描述符唤醒select函数
		
		for(i = 0;i < maxfd + 1;i ++)
		{
			if(FD_ISSET(i,&readfds) != 0)
			{
				if(i == 0)
				{
					memset(buf,0,sizeof(buf));	
					readlen = read(0,buf,sizeof(buf));
					buf[readlen - 1] = '\0';
					printf("stdin:%s\n",buf);
				}

				if(i == sockfd)
				{
					memset(buf,0,sizeof(buf));	
					recvlen = recv(sockfd,buf,sizeof(buf),0);

					buf[recvlen - 1] = '\0';
					printf("recv:%s\n",buf);
				}
			}
		}
	}
	return 0;
}
