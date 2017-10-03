#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(int argc, const char *argv[])
{
	in_addr_t ip;

	ip = inet_addr("192.168.1.2"); //将一个字符串(这个字符串是ip的格式)转化为网络字节序(ip地址的值)

	printf("%#x\n",ip);
	printf("%d\n",ip);

	struct in_addr in;
	in.s_addr = ip;
	char *cip;

	cip = inet_ntoa(in);//将一个ip地址(网络字节序)转化为字符串的格式(点分十进制格式的)
	printf("%s\n",cip);
	return 0;
}
