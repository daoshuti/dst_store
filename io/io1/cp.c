/************************************************************************
   > File Name:    cp.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Wed 28 Sep 2016 04:41:21 PM CST
*******************************************************************/

#include <stdio.h>
int main(int argc, const char *argv[])
{
	FILE *fp1,*fp2;
	char buf[16];
	size_t n;
	if(argc != 3)
	{
		printf("argu error\n");
		return -1;
	}
	fp1 = fopen(argv[1],"r");
	if(fp1 == NULL)
	{
		perror("fopen 1");
		return -1;
	}
	fp2 = fopen(argv[2],"w");
	if(fp2 == NULL)
	{
		perror("fopen 2");
		return -1;
	}
	while(1)
	{
		n = fread(buf,sizeof(char),16,fp1);
		if(n == 0)
		{
			if(feof(fp1) == 0)
			{
				perror("fread");
				return -1;
			}else
				break;
		}
		fwrite(buf,1,n,fp2);

	}
	if(EOF == fclose(fp1))
	{
		perror("fclose 1");
		return -1;
	}
	if(EOF == fclose(fp2))
	{
		perror("fclose 2");
		return -1;
	}

	return 0;
}
