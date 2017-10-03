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

	
	connect(sockfd,(const struct sockaddr *)&seraddr,sizeof(seraddr));
	

	char buf[128];

	while(1)
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf) - 1] = '\0';
		send(sockfd,buf,strlen(buf) + 1,0);

		if(strncmp(buf,"quit",4) == 0)
			break;
	}
	close(sockfd);
	return 0;
}
