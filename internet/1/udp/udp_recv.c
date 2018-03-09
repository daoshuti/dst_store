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

	while(1)
	{
		memset(buf,0,sizeof(buf));
		recvlen = recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&cliaddr,&clilen);
		if(recvlen == -1)
		{
			perror("recvfrom");
			return -1;
		}
		printf("buf:%s,ip:%s\n",buf,inet_ntoa(cliaddr.sin_addr));
	}
	return 0;
}
