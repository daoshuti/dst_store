#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(int argc, const char *argv[])
{
	int sockfd,send_socketfd; 
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{

	}
	struct sockaddr_in seraddr,cliaddr;

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(50000);
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.252");

	if(bind(sockfd,(const struct sockaddr *)&seraddr,sizeof(seraddr)) == -1)
	{

	}

	listen(sockfd,5);

	int clilen = sizeof(cliaddr);

	while(1)//tcp的循环服务器
	{
		send_socketfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
		if(send_socketfd == -1)
		{
			perror("accept");
			return -1;
		}

		int recv_len;
		char buf[128];
		FILE *fp;

		fp = fopen("./2.c","w");
		if(fp == NULL)
		{

		}

		while(1)
		{
			recv_len = recv(send_socketfd,buf,sizeof(buf),0);

			if(recv_len == -1)
			{
				perror("recv");
				return -1;
			}
			
			fwrite(buf,1,recv_len,fp);
			
			if(recv_len < sizeof(buf))
				break;
		}
	}
	close(sockfd);
	close(send_socketfd);
	return 0;
}
