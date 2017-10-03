#include "head.h"

void do_register(int connfd, MSG *pbuf, sqlite3 *db)
{
	char sqlstr[128];
	char *errmsg;

	char **result;
	int nrow;
	int ncolumn;
	sprintf(sqlstr,"select * from usr where name='%s';",pbuf->name);
	if(sqlite3_get_table(db,sqlstr,&result,&nrow,&ncolumn,&errmsg) != SQLITE_OK)
	{
		puts(errmsg);
		sqlite3_free(errmsg);
	}

	if(nrow == 1)
	{
		pbuf->flag = FALSE;
	}
	else 
	{
		sprintf(sqlstr,"insert into usr values ('%s','%s');",pbuf->name,pbuf->data);

		if(SQLITE_OK != sqlite3_exec(db,sqlstr,NULL,NULL,&errmsg))
		{
			puts(errmsg);
			sqlite3_free(errmsg);
		}
		pbuf->flag = TRUE;
	}
	send(connfd, pbuf, sizeof(MSG), 0);
	return;
}

/******************************************************************************/

void do_login(int connfd, MSG *pbuf, sqlite3 *db)
{
	char sqlstr[128];
	char *errmsg, **result;
	int nrow, ncolumn;
	int i;
	int count = 0;
#if 0
	sprintf(sqlstr, "select * from usr;");
	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{
		puts(errmsg);
		sqlite3_free(errmsg);
	}
	printf("nrow = %d\n",nrow);	

	for(i = ncolumn;i < (nrow + 1) * ncolumn;i += ncolumn)
	{
		if(strcmp(result[i],pbuf->name) == 0 && strcmp(result[i + 1],pbuf->data) == 0)
			count ++;
	}
	if(count == 0)
	{
		pbuf->flag = FALSE;
	}
	else 
	{
		pbuf->flag = TRUE;
	}
	send(connfd, pbuf, sizeof(MSG), 0);
#endif 

	sprintf(sqlstr, "select * from usr where name='%s' and passwd='%s';",pbuf->name,pbuf->data);
	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{
		puts(errmsg);
		sqlite3_free(errmsg);
	}
	printf("nrow = %d\n",nrow);	

	if(nrow == 0)
	{
		pbuf->flag = FALSE;
	}
	else 
	{
		pbuf->flag = TRUE;
	}
	send(connfd,pbuf,sizeof(MSG),0);
	sqlite3_free_table(result);

	return;
}

/******************************************************************************/

void get_date(char date[])
{
	time_t t;
	struct tm *tp;

	time(&t);
	
	tp = localtime(&t);
	
	sprintf(date, "%d-%02d-%02d %02d:%02d:%02d", tp->tm_year+1900, 
			tp->tm_mon+1, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);

	return;
}

int do_searchword(int connfd, MSG *pbuf)
{
	FILE *fp;
	char line[300];
	char *p;
	int len, result;

	len = strlen(pbuf->data);
	if ((fp = fopen("dict.txt","r")) == NULL)
	{
		strcpy(pbuf->data, "dict on server can't be opened :");
		send(connfd, pbuf, sizeof(MSG), 0);
	}
	printf("query word is %s\n", pbuf->data);
	while (fgets(line, 300, fp) != NULL)
	{
		result = strncmp(pbuf->data, line, len);
		if (result > 0) 
			continue;
		if (result < 0 || line[len] != ' ') 
			break;
						
		p = line + len;
		while (*p == ' ') 
			p++; 
		strcpy(pbuf->data, p);
		fclose(fp);
		return 1;
	}
	fclose(fp);

	return 0;
}

void do_query(int connfd, MSG *pbuf, sqlite3 *db)
{
	char sqlstr[128], *errmsg;
	int len, result, found = 0;
	char date[64], word[64];
			
	strcpy(word, pbuf->data);
	found = do_searchword(connfd, pbuf);
	if (found)
	{
		get_date(date);
#if 0
		sprintf(sqlstr,"create table record (name,date,word);");
		if(SQLITE_OK != sqlite3_exec(db,sqlstr,NULL,NULL,&errmsg))
		{
			puts(errmsg);
			sqlite3_free(errmsg);
		}
#endif
		sprintf(sqlstr, "insert into record values ('%s', '%s', '%s');", pbuf->name, date, word);
		if (sqlite3_exec(db, sqlstr, NULL, NULL, &errmsg) != SQLITE_OK)
		{
			printf("error : %s\n", errmsg);
			sqlite3_free(errmsg);
		}
	}
	else
	{
		strcpy(pbuf->data, "not found\n");
	}
	send(connfd, pbuf, sizeof(MSG), 0);

	return;
}

/***************************************************************************/

int history_callback(void *arg, int f_num, char **f_value, char **f_name)
{
	int connfd;
	MSG buf;

	connfd = *(int *)arg;
	sprintf(buf.data, "%s : %s", f_value[1],f_value[2]);
	send(connfd, &buf, sizeof(buf),0);

	return 0;
}

void do_history(int connfd, MSG *pbuf, sqlite3 *db)
{
	char sqlstr[128], *errmsg;

	sprintf(sqlstr, "select * from record where name = '%s'", pbuf->name);
	if (sqlite3_exec(db, sqlstr, history_callback, &connfd, &errmsg) != SQLITE_OK)
	{
		printf("error : %s\n", errmsg);
		sqlite3_free(errmsg);
	}
	pbuf->data[0] = '\0';
	send(connfd, pbuf, sizeof(MSG), 0);
	
	return;
}

/******************************************************************************/

void do_client(int connfd, sqlite3 *db)
{
	MSG buf;

	while (recv(connfd, &buf, sizeof(buf), 0) > 0)
	{
		switch (buf.type)
		{
		case R :
			do_register(connfd, &buf, db);
			break;
		case L :
			do_login(connfd, &buf, db);
			break;
		case Q :
			do_query(connfd, &buf, db);
			break;
		case H :
			do_history(connfd, &buf, db);
			break;
		}
	}
	printf("client quit\n");
	exit(0);

	return;
}

int main(int argc, char *argv[])
{
	int listenfd, connfd;
	struct sockaddr_in myaddr;
	pid_t pid;
	MSG buf;
	sqlite3 *db;

	if (argc < 3)
	{
		printf("Usage : %s <ip> <port>\n", argv[0]);
		exit(-1);
	}

	if (sqlite3_open(DATABASE, &db) != SQLITE_OK)
	{
		printf("error : %s\n", sqlite3_errmsg(db));
		exit(-1);
	}

	if ((listenfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}

	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family = PF_INET;
	myaddr.sin_port = htons(atoi(argv[2]));
	myaddr.sin_addr.s_addr = inet_addr(argv[1]);
	if (bind(listenfd, (SA *)&myaddr, sizeof(myaddr)) < 0)
	{
		perror("fail to bind");
		exit(-1);
	}

	if (listen(listenfd, 5) < 0)
	{
		perror("fail to listen");
		exit(-1);
	}

	signal(SIGCHLD, SIG_IGN);
	while (1)
	{
		if ((connfd = accept(listenfd, NULL, NULL)) < 0)
		{
			perror("fail to accept");
			exit(-1);
		}
		if ((pid = fork()) < 0)
		{
			perror("fail to fork");
			exit(-1);
		}
		else if (pid == 0)
		{
			do_client(connfd, db);
		}
		close(connfd);
	}

	return 0;
}
