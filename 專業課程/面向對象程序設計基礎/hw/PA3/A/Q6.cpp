#include <iostream>
using namespace std;
class A {
    int data;
public:
    static int count;
    A():data(2019){count += 1; cout << count << endl;} 
    A& operator = (const A & a){
        if (this != &a) data = a.data;
        return *this;
    }
    A(int i):data(i){count += 2; cout << count << endl;}
    ~A(){cout << "destructor "<< data << endl;}
};
   
class B {
    int data{2020};
    A a1,a2;
public:
    B(){}
    B(int i):a2(i){a1 = a2;}
    ~B(){cout<<"destructor "<< data <<endl;}
};
  
int A::count = 0;

int main() {
    B obj1;
    B obj2(2021);
    return 0;
}