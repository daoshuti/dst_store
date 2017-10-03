#include <iostream>
#include <iomanip>
#include <stdio.h>
/*
 C++的头文件不加.h
 std 标准命名空间
 :: 作用域限定符
 >> 输入定向
 << 输出定向
 using
 using namespace
 C标准库的头文件可以一般不加.h
 printf也可以用
 变量可以在使用时定义，只在该语句块有效
 setw(10)只能填整数（例如10），
      表示空出一段（例：10个）字符空间，后面<<输出的依次从后往前放进去
*/

//using std::cout;
//using std::endl;

using namespace std;

int main()
{
//    std::cout << "Hello World!" << std::endl;
    cout << "Hello World" << endl;
    printf("Hello World \n");
    cout << setw(10) << "123456789" << endl;
    return 0;
}
