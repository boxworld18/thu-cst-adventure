#ifndef _FARM_
#define _FARM_
#include "Cow.h"
using namespace std;

class Farm {
private:
    Cow cow[210];
    int cnt, number;
    double totalMilk;
public:
    Farm(int);
    void addCow(Cow);
    void supply(std::string, int);
    void startMeal();
    void produceMilk();
    double getMilkProduction();
};

#endif