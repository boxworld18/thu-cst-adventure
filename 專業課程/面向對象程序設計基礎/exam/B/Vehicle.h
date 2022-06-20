#pragma once
#include <iostream>
using namespace std;

class Vehicle {
public:
    int MaxWheelNum, MaxWingNum, nowWheel, nowWing;

    Vehicle() {
        MaxWheelNum = MaxWingNum = nowWheel = nowWing = 0;
    }
    
    void set_max_wheel_num(int x) {
        MaxWheelNum = x;
    }

    void set_max_wing_num(int x) {
        MaxWingNum = x;
    }

    void add_wheel() {
        nowWheel ++;
    }

    void add_wing() {
        nowWing ++;
    }

    virtual void run() {
        cout << "I am running" << endl; 
    }
    
    bool finished() {
        if (MaxWheelNum == nowWheel && MaxWingNum == nowWing) return true;
        return false;
    }

    virtual ~Vehicle() {

    }
};