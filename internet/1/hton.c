#include<stdio.h>
#include<arpa/inet.h>

int main(int argc, const char *argv[])
{
	uint32_t hostorder = 0x12345678;

	uint32_t netorder;

	netorder = htonl(hostorder);
	printf("%#x\n",netorder);
	return 0;
}
