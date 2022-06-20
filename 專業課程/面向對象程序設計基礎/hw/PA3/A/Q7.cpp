#include <iostream>
using namespace std;

class Base0{
public:
    Base0(){};
    Base0(int d){};
    void f(double d) { cout << "Base0::f(" << d << ")\n"; }
    void g(double d) { cout << "Base0::h(" << d << ")\n"; }
};
   
class Base1: public Base0{
public:
    using Base0::f;
    void f() { cout << "Base1::f()\n"; }
    void f(int i) { cout << "Base1::f(" << i << ")\n"; }
};

class Derive : public Base1{
public:
    using Base1::f;
    void f(int i) { cout << "Derive::f(" << i << ")\n"; }
};
  
int main() {
    Derive d;
    d.f(10);
    d.f(4.9);
    d.g(4.8);
    d.f();
    return 0;
}
