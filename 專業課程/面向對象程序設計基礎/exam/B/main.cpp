#include <iostream>
#include "Car.h" 
#include "Plane.h" 
#include "Motor.h" 
using namespace std;

int main() {
    int m; 
    cin >> m; 
    Plane* planes = new Plane[1000]; 
    Car* cars = new Car[1000]; 
    Motor* motors = new Motor[1000]; 
    int i_p = 0, i_c = 0, i_m = 0;

    for (int i = 0; i < m; ++i) {
        int op; 
        cin >> op; 
        if (op == 0) {// plane 
            int part; 
            cin >> part; 
            if (part == 0) 
                planes[i_p].add_wing(); 
            else 
                planes[i_p].add_wheel(); 

            if (planes[i_p].finished())
                planes[i_p++].run();
        }
        else if (op == 1) { // car 
            cars[i_c].add_wheel(); 
            if (cars[i_c].finished()) 
                cars[i_c++].run(); 
        }
        else { // motor 
            motors[i_m].add_wheel(); 
            if (motors[i_m].finished())
                motors[i_m++].run(); 
        }
    } 
    return 0;
}