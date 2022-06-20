#include <iostream>
using namespace std;
class A {
public:
    int a=1;
protected:
    int b=2;
private:
    int c=3;
};

class B {
public:
    int d=4;
protected:
    int b=5;
private:
    int e=6;
};
  
class C: public A, private B{
public:
    void print() {
    //    cout << B::b << endl;
    }
};
 
int main() {
    C obj_c;
    obj_c.print();
    cout << obj_c.A::b << endl;
    return 0;
}
