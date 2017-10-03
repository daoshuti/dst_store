#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sqlite3.h>
#include <signal.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define  N  16
#define  R  1   //  user register
#define  L  2   //  user login
#define  Q  3   //  query word
#define  H  4   //  history record
#define  FALSE 5
#define  TRUE  6 
#define DATABASE "my.db"

typedef struct sockaddr SA;

typedef struct 
{
	int type;
	int flag;
	char name[N];
	char data[256];   // password or word
} MSG;

