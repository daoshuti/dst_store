#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>	       /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>

#define CMDSIZE 16
#define NAMESIZE 32
#define PASSWDSIZE 16
#define BUFSIZE 512

#define SERVER_IP_ADDR 172.27.1.15

#define REGISTER 1
#define LOGIN 2
#define QUIT 3
#define QUERY_WORD 1
#define HISTORY_RECORD 2
#define NEXT -1

typedef struct msgnode{
	int type;
	char name[NAMESIZE];
	char passwd[PASSWDSIZE];
	char buf[BUFSIZE];
}MSG;

void register_fun(int sockfd)
{
	printf();
}

int main(int argc, const char *argv[])
{
	int mode = 0;
	int next = 0;
	int sockfd;
	char cmd[CMDSIZE];
	struct sockaddr_in servaddr;

	if(argc != 2){
		fprintf(stderr,"Usage : %s <port>\n",argv[0]);
		exit(-1);
	}

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		perror("socket");
		exit(-1);
	}

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[1]));
	servaddr.sin_addr.s_addr = inet_addr(SERVER_IP_ADDR);

	if(-1 == connect(sockfd,(const struct sockaddr_in *)&servaddr,sizeof(servaddr))){
		perror("connect");
		exit(-1);
	}

	printf("*****************************\n");
	printf("  1:regidter 2:login 3:quit\n");
	printf("*****************************\n\n");
	
	while(1)
	{
		printf("Cmd>");
		fgets(cmd,sizeof(cmd),stdin);
		mode = cmd[0]-'0';
		switch(mode)
		{
			case REGISTER :
				register_fun(sockfd);
				break;
			case LOGIN :
				break;
			case QUIT :
				break;
			default :
				printf("Error : 命令错误\n");
				break;
		}
		if(next)break;
	}

	printf("****************************************\n");
	printf("  1:query_word 2:history_record 3:quit\n");
	printf("****************************************\n\n");
	
	while(1)
	{
		printf("Cmd>");
		fgets(cmd,sizeof(cmd),stdin);
		mode = cmd[0]-'0';
		switch(mode)
		{
			case QUERY_WORD :
				break;
			case HISTORY_RECORD :
				break;
			case QUIT :
				break;
			default :
				printf("Error : 命令错误\n");
				break;
		}
		if(next)break;
	}

Over_end:
	printf("成功退出\n");
	close(sockfd);
	return 0;
}
