#include <iostream>

using namespace std;
//C++可以声明占位符参数，占位符参数一般用于程序扩展和对C代码的兼容
int func(int a, int b, int =0)
{
  return a + b;
}
//默认参
void fun1(int a = 0,int b =0)
{
    cout << "void fun1(int a = 0,int b =0)" << endl;
    cout << "a = "<< a << " b = "<< b << endl;
}
//占位参
void fun2(int ,int )
{
    cout << "void fun2(int ,int )" << endl;
}

int main()
{
    //如果默认参数和占位参数在一起，都能调用起来
    func(1, 2);
    func(1, 2, 3);
    fun1();
    fun1(1);
    fun1(1,2);
    fun2(1,2);
    cout << "Hello world!" << endl;

    return 0;
}
