#include "head.h"

void do_register(int sockfd, MSG *pbuf)
{
	pbuf->type = R;
	printf("input name : ");
	fgets(pbuf->name,sizeof(pbuf->name),stdin);
	pbuf->name[strlen(pbuf->name) - 1] = '\0';

	printf("input password : ");
	fgets(pbuf->data,sizeof(pbuf->data),stdin);
	pbuf->data[strlen(pbuf->data) - 1] = '\0';

	send(sockfd, pbuf, sizeof(MSG), 0);
	recv(sockfd, pbuf, sizeof(MSG), 0);
	if(pbuf->flag == FALSE)
	{
		printf("the user is exist\n");
	}
	else  
	{
		printf("register success\n");
	}
	return ;
}

int do_login(int sockfd, MSG *pbuf)
{
	pbuf->type = L;
	printf("input name : ");
	fgets(pbuf->name,sizeof(pbuf->name),stdin);
	pbuf->name[strlen(pbuf->name) - 1] = '\0';

	printf("input password : ");
	fgets(pbuf->data,sizeof(pbuf->data),stdin);

	pbuf->data[strlen(pbuf->data) - 1] = '\0';
	send(sockfd, pbuf, sizeof(MSG), 0);
	recv(sockfd, pbuf, sizeof(MSG), 0);

	if(pbuf->flag == FALSE)
	{
		printf("the username or password input error\n");
		return 0;
	}
	else
	{
		printf("login success\n");
		return 1;
	}
}

void do_query(int sockfd, MSG *pbuf)
{
	pbuf->type = Q;
	while (1)
	{
		printf("input word(input # go back) :");
		fgets(pbuf->data,sizeof(pbuf->data),stdin);
		pbuf->data[strlen(pbuf->data) - 1] = '\0';

		if (strcmp(pbuf->data, "#") == 0) 
			break;

		send(sockfd, pbuf, sizeof(MSG), 0);
		recv(sockfd, pbuf, sizeof(MSG), 0);

		printf("%s\n",pbuf->data);
	}

	return;
}

void do_history(int sockfd, MSG *pbuf)
{
	pbuf->type = H;
	send(sockfd, pbuf, sizeof(MSG), 0);
	while (1)
	{
		recv(sockfd, pbuf, sizeof(MSG), 0);
		if (pbuf->data[0] == '\0') 
			break;
		printf("%s\n", pbuf->data);
	}

	return;
}

int main(int argc, char *argv[])
{
	int sockfd, login = 0;
	struct sockaddr_in servaddr;
	MSG buf;
	int n;
	char opt[15];

	if (argc < 3)
	{
		printf("Usage : %s <serv_ip> <serv_port>\n", argv[0]);
		exit(-1);
	}

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = PF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);

	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("fail to connect");
		exit(-1);
	}

	while (1)
	{
		printf("************************************\n");
		printf("* 1: register   2: login   3: quit *\n");
		printf("************************************\n");
		printf("please choose : ");

		fgets(opt,sizeof(opt),stdin);
		n = opt[0] - '0';
		switch (n)
		{
		case 1 :
			printf("\n");
			do_register(sockfd, &buf);
			printf("\n");
			break;
		case 2 :
			printf("\n");
			if (do_login(sockfd, &buf) == 1)
			{
				printf("\n");
				while (1)
				{
					printf("***********************************************\n");
					printf("* 1: query_word   2: history_record   3: quit *\n");
					printf("***********************************************\n");
					printf("please choose : ");

					fgets(opt,sizeof(opt),stdin);
					n = opt[0] - '0';
					switch (n)
					{
					case 1 :
						printf("\n");
						do_query(sockfd, &buf);
						printf("\n");
						break;
					case 2 :
						printf("\n");
						do_history(sockfd, &buf);
						printf("\n");
						break;
					case 3 :
						close(sockfd);
						exit(0);
					}
				}

			}
			printf("\n");
			break;
		case 3 :
			close(sockfd);
			exit(0);
		}
	}

	return 0;
}
