#include <cmath>
#include <cstdlib>
//public variables-------------------//
const double pi = 3.1415926535;
extern int OrigX, OrigY, Ratio, Width, Height;
//functions on this page-------------//
double func41(double);
double func42(double);
//-----------------------------------//


double func41(double x) {
	if (x < 0) x *= -1;
    double f = 2 * x - x * x;
    if (f <= 0) return 0;
    return pow(f, 0.5);
}
double func42(double x) {
	if (x < 0) x *= -1;
    double f = x - 1;
    if (f < -1 || f > 1) return 0;
    return asin(x - 1) - pi * 0.5;
}
