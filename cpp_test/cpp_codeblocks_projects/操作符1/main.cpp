#include <iostream>

using namespace std;

class A{
public:
    int i;
    A(){
        i = 100;
    }
    A(int ii){
        i = ii;
    }
};

int main()
{
    A a(200);
    A *a1 = new A();
    int A::* p;//指向类A中int型成员变量的指针
    p = &A::i;//将类A中成员变量i的地址(其实是地址偏移量)赋给p
    cout << "p = " << p << endl;
    cout << a.*(&A::i) << endl;

    cout << a1->*p << endl;
    delete a1;
    cout << "Hello world!" << endl;
    return 0;
}
