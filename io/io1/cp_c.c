/************************************************************************
   > File Name:    cp_c.c
   > Author:       Lin
   > Mail:         linbb@farsight.cn
   > Created Time: Wed 28 Sep 2016 02:46:07 PM CST
*******************************************************************/

#include <stdio.h>
int main(int argc, const char *argv[])
{
	FILE *fp1,*fp2;
	int c;
	//打开文件，拷贝的源文件
	fp1 = fopen("1.txt","r");
	if(fp1 == NULL)
	{
		perror("fopen 1");
		return -1;
	}
	//只写清空方式打开文件，拷贝的目标文件
	fp2 = fopen("2.txt","w");
	if(fp1 == NULL)
	{
		perror("fopen 2");
		return -1;
	}
	//文件指针需要一直进行偏移，偏移文件末尾
	while(1)
	{
		//按字符读取文件
		c = fgetc(fp1);
		if(c == EOF)
		{
			//检查流是否到达文件末尾
			if(feof(fp1) != 0)
				break;
			else
			{
				perror("fgetc");
				return -1;
			}
		}
		//输出到目标文件
		fputc(c,fp2);
	}
	//关闭流
	if(fclose(fp1) == EOF)
	{
		perror("fclose 1");
		return -1;
	}
	if(fclose(fp2) == EOF)
	{
		perror("fclose 2");
		return -1;
	}
	return 0;
}
