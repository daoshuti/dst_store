#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/epoll.h>


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
		
	struct epoll_event ev,events[50];
	//struc epoll_event  epoll的 数据类型
	int nfds,epollfd;

	//通过文件描述符来操作epoll的  
	
	epollfd=epoll_create(50);
	//linux 旧版本 需要填充足够大的个数
	//
	//较近内核  数值填充小了，在后期不影响监控范围  
	if(epollfd<0)
	{
		perror("fail to epoll");
		return -1;
	}

	ev.events=EPOLLIN;   //监视读资源
	ev.data.fd=0;
	if(epoll_ctl(epollfd,EPOLL_CTL_ADD,0,&ev)==-1)
	{
		perror("fail to add fd");
		return -1;
	
	}
	

	ev.events=EPOLLIN;   //监视读资源
	ev.data.fd=sockfd;
	if(epoll_ctl(epollfd,EPOLL_CTL_ADD,sockfd,&ev)==-1)
	{
		perror("fail to add fd");
		return -1;
	
	}

	//epoll 对于select   1    :添加一次，不需要重复添加   

	while(1)	
	{
	nfds=epoll_wait(epollfd,events,50,-1);//等同于  select
	//1. epollfd   属于  代表epoll操作的文件描述符
	//2. 结果返回的数组   
	//
	//epoll 优点2    就绪的结果会返回出来   并且按照数组元素从0 ....
	//
	//3.最大监控个数
	//4. 超时   -1代表不监视
	//
	//nfds  就绪的个数   
	
	if(nfds<0)
	{
		perror("fail to epoll_wait");
		return -1;
	
	}
	int i;
	for(i=0;i<nfds;i++)//就绪结构体已经放置在envents数组里  个数也告诉你
	{
		if(events[i].data.fd==sockfd)
		{
			confd=accept(sockfd,NULL,NULL);
			printf("confd:%d\n",confd);
			if(confd<0)
			{
				perror("fail to accept");
				return -1;
			}
			ev.events=EPOLLIN;   //监视读资源
			ev.data.fd=confd;
			if(epoll_ctl(epollfd,EPOLL_CTL_ADD,confd,&ev)==-1)
			{
				perror("fail to add fd");
				return -1;
	
			}

		
		
		}
		else if(events[i].data.fd==0)
		{
			bzero(buf,sizeof(buf));
			fgets(buf,sizeof(buf),stdin);
			printf("fgets:%s\n",buf);
		
		}
		else
		{
			bzero(buf,sizeof(buf));
			ret_recv=recv(events[i].data.fd,buf,sizeof(buf),0);
			if(ret_recv<0)
			{
				perror("fail to recv");
				return -1;
			
			}
			else if(ret_recv==0)
			{
				printf("peer is closed :%d\n",events[i].data.fd);
			//	close(events[i].data.fd);
				if(epoll_ctl(epollfd,EPOLL_CTL_DEL,events[i].data.fd,NULL)==-1)
				{
					perror("fail to epoll_ctl_del");
					return -1;
				
				}
				close(events[i].data.fd);
			
			
			}
			else
			{
				printf("recv:%s\n",buf);
				send(events[i].data.fd,buf,sizeof(buf),0);
			
			}
		
		
		}
	
	}


	}

#if 0
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
#endif 
	
	return 0;
}
