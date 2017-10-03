#include <iostream>

using namespace std;
class A{
    int a;
    int b;
public:
    A(){a=0; b=0;}
    A(int a,int b){this->a=a;this->b=b;};
    int getA(){return a;}
    int getB(){return b;};
};

int main()
{
    A *a = new A();
    delete a;
//    A b[2]={A(1,2),A(3,4)};
//    cout << b[0].getA()<<endl;
//    cout << b[0].getB()<<endl;
//    cout << b[1].getA()<<endl;
//    cout << b[1].getB()<<endl;
    A *c = new A[2]{A(1,2),A(3,4)};
    cout << (*c).getA()<<endl;
    cout << c[0].getB()<<endl;
    cout << c[1].getA()<<endl;
    cout << c[1].getB()<<endl;
    delete[] c;

    cout << "Hello world!" << endl;
    return 0;
}
