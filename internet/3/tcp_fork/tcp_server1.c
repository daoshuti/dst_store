#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>

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
	
	/*僵尸进程产生:子进程退出，父进程没有回收子进程的资源。同时父进程还捕捉到了SIGCHLD信号*/

	/*SIGCHLD由于子进程退出产生的一个信号发送给父进程，说明父进程默认是关心SIGCHLD信号的
	 * 一旦关心SIGCHLD信号则会产生僵尸进程*/
	signal(SIGCHLD,SIG_IGN);

	pid_t pid,pid1;
	int clilen = sizeof(cliaddr);
	char buf[128];
	int recv_len;
	while(1)
	{
		msgfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
		if(msgfd == -1)
		{
			perror("accept");
			return -1;
		}

		pid = fork();

		if(pid == -1)
		{

		}
		else if(pid == 0)//用于跟客户端收发数据
		{
			close(sockfd);
#if 1
			while(1)
			{
				memset(buf,0,sizeof(buf));
				recv_len = recv(msgfd,buf,sizeof(buf),0);
				buf[recv_len - 1] = '\0';
				if(strncmp(buf,"quit",4) == 0)
					exit(EXIT_SUCCESS);
				printf("%s\n",buf);
			}
#endif

		}
		else //用于跟客户端建立连接
		{
			close(msgfd);
		}
	}

	return 0;
}
