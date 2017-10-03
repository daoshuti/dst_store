#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>

struct msg
{
	char name[15];
	char buf[128];
	char type;
};

typedef struct node
{
	struct sockaddr_in data;
	struct node *next;
}listnode;

listnode *create_head()
{
	listnode *H;

	H = malloc(sizeof(listnode));

	H->next = NULL;

	return H;
}

void login(listnode *H,struct sockaddr_in cliaddr,int sockfd,struct msg info)
{
	listnode *p;

	p = malloc(sizeof(listnode));

	p->data = cliaddr;

	p->next = H->next;
	H->next = p;

	p = H->next;

	while(p != NULL)
	{
		if(memcmp(&p->data,&cliaddr,sizeof(cliaddr)) != 0)
			sendto(sockfd,&info,sizeof(info),0,(struct sockaddr *)&p->data,sizeof(p->data));
		p = p->next;
	}

}

void msg_quit(listnode *H,struct sockaddr_in cliaddr,int sockfd,struct msg info)
{
	listnode *p = H;
	listnode *q;
	while(p->next != NULL)
	{
		if(memcmp(&p->next->data,&cliaddr,sizeof(cliaddr)) == 0)
		{
			q = p->next;
			p->next = q->next;

			free(q);
			q = NULL;
		}
		else 
		{
			sendto(sockfd,info.buf,sizeof(info.buf),0,(struct sockaddr *)&p->next->data,sizeof(p->next->data));
			p = p->next;
		}
	}
}


void send_msg(listnode *H,struct sockaddr_in cliaddr,int sockfd,struct msg info)
{
	listnode *p = H->next;
	while(p != NULL)
	{
		if(memcmp(&p->data,&cliaddr,sizeof(cliaddr)) != 0)
			sendto(sockfd,&info,sizeof(info),0,(struct sockaddr *)&p->data,sizeof(p->data));
		p = p->next;
	}

}
int main(int argc, const char *argv[])
{
	int sockfd;
	listnode *H;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd == -1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in seraddr,cliaddr;
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(50000);
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.252");

	if(bind(sockfd,(const struct sockaddr *)&seraddr,sizeof(seraddr)) == -1)
	{

	}
	
	H = create_head();

	struct msg info;
	int clilen = sizeof(cliaddr);
	while(1)
	{
		recvfrom(sockfd,&info,sizeof(info),0,(struct sockaddr *)&cliaddr,&clilen);

		switch(info.type)
		{
		case 'L':
			login(H,cliaddr,sockfd,info);
			break;
		case 'S':
			send_msg(H,cliaddr,sockfd,info);
			break;
		case 'Q':
			msg_quit(H,cliaddr,sockfd,info);
			break;
		}
	}
	return 0;
}
