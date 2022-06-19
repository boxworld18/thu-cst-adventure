#include <cmath>

//public variables-------------------//
const double pi = 3.1415926535;
const double k = 0.008;
extern int OrigX, OrigY, Ratio, Width, Height;
//functions on this page-------------//
double func51(double);
double func52(double);
double func511(double);
double func512(double);
double func521(double);
double func522(double);
//-----------------------------------//

double func511(double t) {
    return k * (- t * t + 40 * t + 1200) * sin(pi * t / 180);
}
double func512(double t) {
    return k * (- t * t + 40 * t + 1200) * cos(pi * t / 180) - 5;
}
double func521(double t) {
    return - k * (- t * t + 40 * t + 1200) * sin(pi * t / 180);
}
double func522(double t) {
    return k * (- t * t + 40 * t + 1200) * cos(pi * t / 180) - 5;
}
double func51(double t) {
    return 16 * sin(t) * cos(t) * log(abs(t));
}
double func52(double t) {
    return 16 * sqrt(abs(t)) * cos(t) - 5;
}