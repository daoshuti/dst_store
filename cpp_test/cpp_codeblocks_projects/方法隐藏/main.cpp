#include <iostream>

using namespace std;
class A{
public:
    void fun(){
        cout << "A::fun" << endl;
    }
    void fun(int i){
        cout << "A::fun(int i)" << endl;
    }
};

class B : public A{
public:
    void fun(){
        cout << "B::fun" << endl;
    }
    void fun(int i){
        cout << "B::fun(int i)" << endl;
    }
};
int main()
{
    B b;
    b.fun(1);
    cout << "Hello world!" << endl;
    return 0;
}
