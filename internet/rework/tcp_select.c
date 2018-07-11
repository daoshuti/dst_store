#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
 #include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>


#define SA struct sockaddr
int main(int argc, const char *argv[])
{
	int sockfd,confd;

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("fail to socket");
		return -1;

	}
	struct sockaddr_in seraddr;
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(50000);
	seraddr.sin_addr.s_addr=inet_addr("0.0.0.0");


	int ret_bind;
	ret_bind=bind(sockfd,(SA *)&seraddr,sizeof(seraddr));
	if(ret_bind<0)
	{
		perror("fail to bind");
		return -1;

	}


	listen(sockfd,5);
	//建立一个  backlog大小的  队列（顺序）
	//用来为 accept 服务
	char buf[128];
	int ret_recv;
	int ret_select;
	int maxfd;
	fd_set current, global;
	FD_ZERO(&current);
	FD_ZERO(&global);

	FD_SET(0,&global);
	FD_SET(sockfd,&global);
	maxfd=sockfd;
	int i;

	while(1)
	{
		current=global;

		ret_select=select(maxfd+1,&current,NULL,NULL,NULL);
		if(ret_select<0)
		{
			perror("fail to select");
			return -1;
		
		}

		if(FD_ISSET(0,&current))
		{
			bzero(buf,sizeof(buf));
			fgets(buf,sizeof(buf),stdin);
			printf("fgets-buf:%s\n",buf);
		
		}
		if(FD_ISSET(sockfd,&current))
		{
			confd=accept(sockfd,NULL,NULL);
			if(confd<0)
			{
				perror("fail to accept");
				return -1;
			}
			FD_SET(confd,&global);
			printf("sockfd:%d confd: %d\n",sockfd,confd);
			if(confd>maxfd)
				maxfd=confd;
		}

		for(i=3;i<=maxfd;i++)
		{
			bzero(buf,sizeof(buf));
			if(sockfd==i)
				continue;

			if(FD_ISSET(i,&current))
			{
				ret_recv=recv(i,buf,sizeof(buf),0);
			
				if(ret_recv<0)
				{
					perror("fail to recv");
					return -1;
				
				}
				if(ret_recv==0)
				{
					close(i);
					printf("peer is closed: confd=%d\n",i);

					FD_CLR(i,&global);

					if(i==maxfd)
					{
						while(maxfd--)
						{
							if(FD_ISSET(maxfd,&global))
							break;
						
						}
	
					}
			
				
				}

				printf("recv-buf:%s\n",buf);

				send(i,buf,sizeof(buf),0);
			
			}

		
		
		
		}


	}

	
	return 0;
}
