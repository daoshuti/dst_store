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
	seraddr.sin_addr.s_addr = inet_addr("224.0.0.1");

	if(bind(sockfd,(const struct sockaddr *)&seraddr,sizeof(seraddr)) == -1)
	{

	}
	struct ip_mreqn multiaddr;
	multiaddr.imr_address.s_addr = inet_addr("172.27.1.252"); //本机ip
	multiaddr.imr_multiaddr.s_addr = inet_addr("224.0.0.1");//组ip
	multiaddr.imr_ifindex = 0;//网卡编号
	setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&multiaddr,sizeof(multiaddr));
	//以上代码的作用，就是将本机ip地址添加到组播地址中
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
