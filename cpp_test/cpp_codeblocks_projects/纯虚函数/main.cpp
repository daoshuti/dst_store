#include <iostream>

using namespace std;

class A {
public:
    virtual void fun()=0;
};
class B {
public:
    void fun(){
        cout << "B类中重写父类（A）的纯虚函数" << endl;
    }
};

int main()
{
    B b;
    b.fun();
    cout << "Hello world!" << endl;
    return 0;
}

