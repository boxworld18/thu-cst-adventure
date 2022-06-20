#include<iostream>
#include"Vehicle.h"
using namespace std;

class Car: public Vehicle { 
    public:
        Car() {
            set_max_wheel_num(4);
            set_max_wing_num(0);
        }
        void run() {
            cout << "I am running" << endl;
        }
};