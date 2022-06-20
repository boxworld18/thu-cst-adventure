#pragma once
#include <math.h>

class PerformStrategy {
protected:
    double perform;
public:
    PerformStrategy(double);
    virtual int getTotal(int) = 0;
};

class sPerformStrategy: public PerformStrategy {
public:
    using PerformStrategy::PerformStrategy;
    int getTotal(int);
};

class mPerformStrategy: public PerformStrategy {
public:
    using PerformStrategy::PerformStrategy;
    int getTotal(int);
};

class lPerformStrategy: public PerformStrategy {
public:
    using PerformStrategy::PerformStrategy;
    int getTotal(int);
};