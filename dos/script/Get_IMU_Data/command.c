/*************************************************************************
 @Author: wanghan
 @Created Time : 2018/3/6 15:43:16
 @File Name: 1.c
 @Description:
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGHT 1024

int main(int argc, const char* argv[])
{
	FILE* pipe = NULL;
	char ch = 0;
	int count = 0, line_number = 0;
	char buffer[BUFFER_LENGHT];

	pipe = _popen("adb shell imutool", "r");
	if (!pipe) return -1;//返回0表示运行失败

	while(!feof(pipe))
	{
		ch = fgetc(pipe);
		while('\n' != ch)
		{
			buffer[count++] = ch;
			ch = fgetc(pipe);//fgets(buffer, sizeof(buffer), pipe);
            if ('\t' == ch) ch = ',';
		}
		count = 0;
        line_number++;
		printf("%d, %s\n", line_number, buffer);
		memset(buffer, 0, sizeof(buffer));
	}
	_pclose(pipe);

	getchar();
	return 0;
}
