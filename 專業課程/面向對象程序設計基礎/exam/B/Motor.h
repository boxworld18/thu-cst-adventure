#include<iostream>
#include"Vehicle.h"
using namespace std;

class Motor: public Vehicle { 
    public:
        Motor() {
            set_max_wheel_num(2);
            set_max_wing_num(0);
        }
};