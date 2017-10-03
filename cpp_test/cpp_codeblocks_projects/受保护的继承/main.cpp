#include <iostream>

using namespace std;

class A {
public:
    int i;
private:
    int j;
protected:
    int k;
};

class B : protected A{
public:
    int l;
    void fun(){
        i = 1;
        k = 2;
    }
};

int main()
{
    B b;
//    b.i = 1;
    cout << "Hello world!" << endl;
    return 0;
}
