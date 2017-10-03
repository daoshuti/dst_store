#include <stdio.h>;
#include <string.h>;
//#include <stdarg.h>;

typedef char * va_list;

#define _INTSIZEOF(n) ((sizeof(n)+sizeof(int)-1)&~(sizeof(int) - 1) )

#define va_start(ap,v) ( ap = (va_list)&v + _INTSIZEOF(v) )

#define va_arg(ap,t) ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )

#define va_end(ap) ( ap = (va_list)0 )

/* ANSI标准形式的声明方式，括号内的省略号表示可选参数 */

int demo(char *msg, ... )
{
    va_list argp;                   /* 定义保存函数参数的结构 */
    int argno = 0;                  /* 纪录参数个数 */
    char *para;                     /* 存放取出的字符串参数 */

/* argp指向传入的第一个可选参数，msg是最后一个确定的参数 */
    va_start( argp, msg );

    while (1)
    {
        para = va_arg( argp, char *);  /*取出当前的参数，类型为char *. */
        if ( strcmp( para, "\0") == 0 )/* 采用空串指示参数输入结束 */
            break;
        printf("Parameter #%d is: %s \n", argno, para);
        argno++;
    }
    va_end( argp ); /* 将argp置为NULL */
    return 0;
}


int main( void )
{
    demo("DEMO", "This", "is", "a", "demo!" ,"333333", "\0");
    return 0;
}
