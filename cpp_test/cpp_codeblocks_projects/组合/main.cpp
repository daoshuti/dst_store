#include <iostream>

using namespace std;

class Engine{
public:
    Engine(){
        cout << "Engine" << endl;
    }
    void fire(){
        cout << "fire" << endl;
    }
    ~Engine(){
        cout << "~Engine" << endl;
    }
};

class Door{
public:
    Door(){
        cout << "Door" << endl;
    }
    void open(){
        cout << "door open" << endl;
    }
    void close(){
        cout << "door close" << endl;
    }
    ~Door(){
        cout << "~Door" << endl;
    }
};

class Wheel{
public:
    Wheel(){
        cout << "Wheel" << endl;
    }
    void run(){
        cout << "run" << endl;
    }
    void stop(){
        cout << "stop" << endl;
    }
    ~Wheel(){
        cout << "~Wheel" << endl;
    }
};

class Car{
public:
    Car(){
        cout << "Car" << endl;
    }
    Engine engine;
    Wheel wheel;
    Door door;
    ~Car(){
        cout << "~Car" << endl;
    }
};

class BMW : public Car{
public:
    BMW(){
        cout << "BMW" << endl;
    }
    ~BMW(){
        cout << "~BMW" << endl;
    }
};

int main()
{
    Car bmw;
    cout << "------------------" << endl;
    BMW mycar;
    cout << "------------------" << endl;
    bmw.engine.fire();
    bmw.door.open();
    bmw.door.close();
    bmw.wheel.run();
    bmw.wheel.stop();
    cout << "------------------" << endl;
    cout << "Hello world!" << endl;
    return 0;
}
