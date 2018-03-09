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

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(50000);
	addr.sin_addr.s_addr = inet_addr("172.16.12.244");//"172.25.1.252"
#if 0
	if(bind(sockfd,(const struct sockaddr *)&addr,sizeof(addr)) == -1)
	{
		perror("bind");
		return -1;
	}
#endif 

	char buf[128];
	
	memset(buf,0,sizeof(buf));
	fgets(buf,sizeof(buf),stdin);

	sendto(sockfd,buf,strlen(buf)+1,0,(const struct sockaddr *)&addr,sizeof(addr));

	return 0;
}
