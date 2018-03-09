#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024

int main(int argc, const char* argv[])
{
	FILE* pipe = NULL;
	char ch = 0;
	int count = 0;
    unsigned int line_num = 0;
	char buffer[BUF_SIZE];
    
	pipe = _popen("adb shell imutool", "r");
	if (!pipe) return -1;//返回0表示运行失败

    printf("No,Time (s),Temperature (C),Gyro_x,Gyro_y,Gyro_z,Accel_x,Accel_y,Accel_z,Mag_x,Mag_y,Mag_z\n");
	while(!feof(pipe))
	{
        memset(buffer, 0, sizeof(buffer));
		while('\n' != ch)
		{
            ch = fgetc(pipe);
            if ('\t' == ch) ch = ',';
			buffer[count++] = ch;
		}
        ch =0;
		count = 0;

        printf("%d,%s", line_num++, buffer);
	}
	_pclose(pipe);

	getchar();
	return 0;
}

