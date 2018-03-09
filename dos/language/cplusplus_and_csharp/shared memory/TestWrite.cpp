#include <iostream>  
#include <windows.h>  
using namespace std;  
  
#define BUF_SIZE 1024  
char szName[] = "testmap";    // 共享内存的名字  

void LockMutex(HANDLE m_hMutex)
{
    DWORD dRes = -1;
    dRes = WaitForSingleObject(m_hMutex, INFINITE);
    if(WAIT_OBJECT_0  == dRes) cout<<"上锁成功!"<<endl;
    else if(WAIT_ABANDONED == dRes) cout<<"发生锁死现象"<<endl;
    else if(WAIT_TIMEOUT == dRes) cout<<"等待超时"<<endl;
    else if(WAIT_FAILED == dRes) cout<<"发生错误"<<endl;
    else cout<<"上锁失败!"<<endl;
}

int main()  
{
    char szInfo[BUF_SIZE] = {0};

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
    
    while(1)  
    {
        cout << "input..." << endl;
        gets(szInfo); // 其实gets并不安全  
        LockMutex(mutex);
        memset(pBuf, 0, BUF_SIZE);
        strncpy(pBuf, szInfo, BUF_SIZE);
        //strncpy(pBuf, "debug", 5);
        ReleaseMutex(mutex);cout<<"解锁完成!"<<endl;
    }  
  
    UnmapViewOfFile(pBuf);  
    CloseHandle(hMapFile);  
    return 0;  
}  
