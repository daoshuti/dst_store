#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>

#define DEBUG_ENABLE 0
#define BUF_SIZE 1024
char szName[] = "testmap";    // 共享内存的名字

void LockMutex(HANDLE m_hMutex)
{
    DWORD dRes = -1;
    dRes = WaitForSingleObject(m_hMutex, INFINITE);
#if DEBUG_ENABLE
    if(WAIT_OBJECT_0  == dRes) printf("上锁成功!\n");
    else if(WAIT_ABANDONED == dRes) printf("发生锁死现象!\n");
    else if(WAIT_TIMEOUT == dRes) printf("等待超时!\n");
    else if(WAIT_FAILED == dRes) printf("发生错误!\n");
    else printf("上锁失败!\n");
#endif
}

int main(int argc, const char* argv[])
{
	FILE* pipe = NULL;
	char ch = 0;
	int count = 0;
    unsigned int line_num = 0;
	char buffer[BUF_SIZE];
    char temp_buffer[BUF_SIZE];
    // 创建共享文件句柄  
    HANDLE hMapFile = CreateFileMapping(  
        INVALID_HANDLE_VALUE,    // 物理文件句柄  
        NULL,                    // 默认安全级别  
        PAGE_READWRITE,          // 可读可写  
        0,                       // 高位文件大小  
        BUF_SIZE,                // 地位文件大小  
        szName          // 共享内存名称  
        );  

    char *pBuf = (char *)MapViewOfFile(  
        hMapFile,            // 共享内存的句柄  
        FILE_MAP_ALL_ACCESS, // 可读写许可  
        0,  
        0,  
        BUF_SIZE  
        );  

    // 定义进程锁
    HANDLE mutex;
	char mutexname[] = "testmapmutex";
    mutex = OpenMutex(MUTEX_ALL_ACCESS,FALSE,mutexname);
    if(mutex == NULL)  
    {
        mutex = CreateMutex(NULL,FALSE,mutexname);  
    }
    
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

        printf("%d,%s", line_num, buffer);
        memset(temp_buffer, 0, BUF_SIZE);
        sprintf(temp_buffer, "%d,%s", line_num++, buffer);
        
        LockMutex(mutex);
        memset(pBuf, 0, BUF_SIZE);
        strcpy(pBuf, temp_buffer);
        ReleaseMutex(mutex);

#if DEBUG_ENABLE
        printf("解锁完成!\n");
#endif

	}
	_pclose(pipe);

	getchar();
	return 0;
}

