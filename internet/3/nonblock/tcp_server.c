#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>


int main(int argc, const char *argv[])
{
	int sockfd,send_socketfd; 
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

	while(1)//tcp的循环服务器
	{
		send_socketfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
		if(send_socketfd == -1)
		{
			perror("accept");
			return -1;
		}

		int recv_len;
		char buf[128] = {0};
		int flag;
		
		flag = fcntl(send_socketfd,F_GETFL);
		flag |= O_NONBLOCK;
		fcntl(send_socketfd,F_SETFL,flag);

		while(1)
		{
			recv_len = recv(send_socketfd,buf,sizeof(buf),0);

#if 0
			if(recv_len == -1)
			{
				perror("recv");
				return -1;
			}
#endif
			if(strncmp(buf,"quit",4) == 0)
				break;

			printf("recv_len = %d\n",recv_len);
			printf("%s\n",buf);
			sleep(1);
		}
	}
	close(sockfd);
	close(send_socketfd);
	return 0;
}
