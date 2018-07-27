/*************************************************************************
 @Author: wanghan
 @Created Time : Mon 23 Jul 2018 02:39:16 PM CST
 @File Name: print.c
 @Description:
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    int i;
    char string_line[1024] = {};
    for(i=0;i<=100;i++){
        sprintf(string_line,"\r%02d percent",i);
        printf(string_line);
        fflush(stdout);
        sleep(1);
    }
    return 0;
}
