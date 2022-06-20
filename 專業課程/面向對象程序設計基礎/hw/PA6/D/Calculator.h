#pragma once
#include "LevelStrategy.h"
#include "PerformStrategy.h"

class Calculator {		
    LevelStrategy* ls;
    PerformStrategy* ps;			
public:
    Calculator(LevelStrategy*, PerformStrategy*);
    int get_base();
    int get_total(int);
    ~Calculator();
};