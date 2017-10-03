#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

int main(int argc, const char *argv[])
{
	int sockfd,send_socketfd; 
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{

	}
	struct sockaddr_in seraddr;

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(50000);
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.252");

	
	if(connect(sockfd,(const struct sockaddr *)&seraddr,sizeof(seraddr)) == -1)
	{
		perror("connect");
		return -1;
	}
	

	char buf[10];
	
	FILE *fp;
	ssize_t n;
	fp = fopen("./1.c","r");
	if(fp == NULL)
	{
		perror("fopen");
		return -1;
	}
	while(1)
	{
		n = fread(buf,1,sizeof(buf),fp);

		if(n < sizeof(buf) && feof(fp) == 0)
		{
			perror("fread");
			return -1;
		}

		send(sockfd,buf,n,0);
		if(n < sizeof(buf) && feof(fp) != 0)
			break;
	}
	close(sockfd);
	return 0;
}
