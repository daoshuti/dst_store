/************************************************************************
   > File Name:    write.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Mon 10 Oct 2016 09:40:39 AM CST
*******************************************************************/

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define SIZE 64
typedef struct msgbuf
{
	long type;
	char buf[SIZE];
}MSG;
int main(int argc, const char *argv[])
{
	key_t key;
	int msgid;
	MSG msgb;
	key = ftok(".",'n');
	if(key == -1)
	{
		perror("ftok");
		return -1;
	}
	msgid = msgget(key,IPC_CREAT|IPC_EXCL|0666);
	if(-1 == msgid)
	{
		if(errno == EEXIST)
		{
			msgid = msgget(key,0);
		}else
		{
			perror("msgget");
			return -1;
		}
	}
	printf("msgid = %d\n",msgid);
	msgb.type = 250;
	while(1)
	{
		fgets(msgb.buf,SIZE,stdin);
		if(-1 == msgsnd(msgid,&msgb,SIZE,0))
		{
			perror("msgsnd");
			return -1;
		}
		if(0 == strncmp(msgb.buf,"quit",4))
			break;
	}
	return 0;
}
