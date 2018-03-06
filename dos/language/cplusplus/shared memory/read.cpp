#include <iostream>  
#include <windows.h>  
using namespace std;  
  
#define BUF_SIZE 1025  
char szName[] = "testmap";    // 共享内存的名字  
  
int main()  
{  
    // 创建共享文件句柄  
    HANDLE hMapFile = CreateFileMapping(  
        INVALID_HANDLE_VALUE,    // 物理文件句柄  
        NULL,                    // 默认安全级别  
        PAGE_READWRITE,          // 可读可写  
        0,                       // 高位文件大小  
        BUF_SIZE,                // 地位文件大小  
        szName                   // 共享内存名称  
        );  
  
  
    char *pBuf = (char *)MapViewOfFile(  
        hMapFile,            // 共享内存的句柄  
        FILE_MAP_ALL_ACCESS, // 可读写许可  
        0,  
        0,  
        BUF_SIZE  
        );  
  
    while(1)  
    {  
        cout << "press any button to receive data..." << endl;  
        getchar();  
        cout << pBuf << endl;  
    }  
  
    UnmapViewOfFile(pBuf);  
    CloseHandle(hMapFile);  
    return 0;  
}  