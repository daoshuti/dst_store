#include <iostream>

using namespace std;

class A{
public:
    virtual void fun(){
        cout << "virtual void A::fun()" << endl;
    }
};
class B : public A{
public:
    virtual void fun(){
        cout << "virtual void B::fun()" << endl;
    }
};

void fun(A &a)
{
    a.fun();
}
int main()
{
    B b;
    fun(b);
    cout << "sizeof(A) : " << sizeof(A) << endl;
    cout << "sizeof(B) : " << sizeof(B) << endl;
    cout << "Hello world!" << endl;
    return 0;
}
