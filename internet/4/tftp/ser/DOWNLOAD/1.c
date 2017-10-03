#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<dirent.h>

#define SEARCH 1
#define DOWN 2

#define FALSE 3
#define TRUE 4
typedef struct tftp
{
	int type;
	int flag;
	char buf[128];
	char fname[15];
}tftp_t;

void search_file(tftp_t info,int msgfd)
{
	DIR *pdir;
	struct dirent *rdir;	
	pdir = opendir("./DOWNLOAD/");

	memset(info.buf,0,sizeof(info.buf));
	while((rdir = readdir(pdir)) != NULL)
	{
		if(rdir->d_name[0] == '.')	
			continue;
		
		strcat(info.buf,rdir->d_name);
		info.buf[strlen(info.buf)] = ' ';
	}
	send(msgfd,&info,sizeof(info),0);
}

void tftp_down(tftp_t info,int msgfd)
{
	char word[100];

	sprintf(word,"./DOWNLOAD/%s",info.fname);

	FILE *fp;
	ssize_t len;
	fp = fopen(word,"r");

	if(fp == NULL)
	{
		info.flag = FALSE;
	}
	else 
		info.flag = TRUE;
	send(msgfd,&info,sizeof(info),0);

	while(1)
	{
		len = fread(info.buf,1,sizeof(info.buf),fp);

		send(msgfd,info.buf,len,0);	
		if(len < sizeof(info.buf) && feof(fp) != 0)
			break;

	}
	fclose(fp);

}

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
	int recv_len;
	tftp_t info;
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
			
			while(1)
			{
				recv_len = recv(msgfd,&info,sizeof(info),0);

				switch(info.type)
				{
				case SEARCH:
					search_file(info,msgfd);
					break;
				case DOWN:
					tftp_down(info,msgfd);
					break;
				}
			}

		}
		else //用于跟客户端建立连接
		{
			close(msgfd);
		}
	}

	return 0;
}
