#include <iostream>

using namespace std;

class myclass {
public:
    int sum;
    void sum_it(int x);
};

void myclass::sum_it(int x)
{
    int i;
    sum = 0;
    for(i = x; i; i--) sum += i;
}

int main()
{
    int myclass::*dp;        //指向 myclass 中整数类型成员变量的指针
    void (myclass::*fp)(int x);        //指向myclass 中成员函数的指针
    myclass c;
    dp = &myclass::sum;        //获得成员变量的地址
    fp = &myclass::sum_it;    //获得成员函数的地址
    (c.*fp)(7);       //计算 1 到 7 相加的和
    cout << "summation of 7 is " << c.*dp;

    return 0;
}
