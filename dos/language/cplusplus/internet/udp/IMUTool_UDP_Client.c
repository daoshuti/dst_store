#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib,"WS2_32.lib ")

int main(int argc, const char *argv[])
{
	char buf[128];
	SOCKET sockfd;
	struct sockaddr_in addr;

	int ret;

    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;

    ret = WSAStartup(wVersionRequested, &wsaData);
    if (ret != 0) {
        printf("WSAStartup() called failed!\n");
        return -1;
    }
    else {
        printf("WSAStartup() called success!\n");
    }

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        //若不是所请求的版本号2.2,则终止WinSock库的使用
        WSACleanup();
        return -1;
    }

	sockfd = socket(AF_INET,SOCK_DGRAM,0);//IPPROTO_UDP
	if(sockfd == -1)
	{
		perror("socket fail!");
		getchar();
		return -1;
	}

	//PSOCKADDR_IN addr = (SOCKADDR_IN)malloc(sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(50000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");//"172.16.12.244"
#if 0
	if(bind(sockfd,(const struct sockaddr *)&addr,sizeof(addr)) == -1)
	{
		perror("bind fail");
        getchar();
		return -1;
	}
#endif 

	while(1)
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf) - 1] = '\0';
		sendto(sockfd, buf, strlen(buf)+1, 0, (const struct sockaddr *)&addr, sizeof(addr));
	}

	closesocket(sockfd);
    WSACleanup();
	return 0;
}
