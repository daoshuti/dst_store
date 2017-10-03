#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<sys/select.h>


int main(int argc, const char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr,"error\n");
		return -1;
	}

	int sockfd,msgfd; 
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{

	}
	struct sockaddr_in seraddr,cliaddr;

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(atoi(argv[1]));
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.252");

	if(bind(sockfd,(const struct sockaddr *)&seraddr,sizeof(seraddr)) == -1)
	{

	}

	listen(sockfd,5);
	

	int clilen = sizeof(cliaddr);
	int n;
	fd_set readfds;
	fd_set currentfds;
	int maxfd = sockfd;
	FD_ZERO(&readfds);
	FD_ZERO(&currentfds);

	FD_SET(sockfd,&readfds);
	
	int i;
	int recvlen;
	char buf[128];

	struct timeval t;

	while(1)
	{
		t.tv_sec = 5;
		t.tv_usec = 0;
		currentfds = readfds;
		n = select(maxfd + 1,&currentfds,NULL,NULL,&t);

		if(n == -1)
		{
			printf("select 调用出错\n");
			continue;
		}
		
		if(n == 0)
		{
			printf("time out\n");
			continue;
		}

		if(FD_ISSET(sockfd,&currentfds) != 0)
		{
			msgfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);

			FD_SET(msgfd,&readfds);

			if(msgfd > maxfd)
				maxfd = msgfd;
		}

		for(i = 3;i < maxfd + 1;i ++)
		{
			if(i == sockfd)
				continue;
			if(FD_ISSET(i,&currentfds) != 0)
			{
			//	while(1)
			//	{
				memset(buf,0,sizeof(buf));
				recvlen = recv(i,buf,sizeof(buf),0);

				if(recvlen == -1)
				{
					printf("接收失败\n");
					break;
				}
				else if(recvlen == 0)//客户端正常退出
				{
					close(i);	
					FD_CLR(i,&readfds);

					if(i == maxfd)
					{
						while(maxfd --)
						{
							if(FD_ISSET(maxfd,&readfds) != 0)
								break;
						}
					}
				}
				else 
				{
					buf[recvlen - 1] = '\0';
					printf("recv %s\n",buf);
				}
			//	}
			}
		}
		
	}

	return 0;
}
