#pragma once
#include "Pair.h"

class Map{
    Pair * data[100010];
    int sz;
public:
    Map(int n);
    // TODO
    int& operator[](std::string str) {
        for (int i = 0; i < sz; i++)
        if (data[i] -> hasKey(str)) {
            return data[i] -> getVal();
        }
        data[sz] -> reset(str, 0);
        return data[sz++] -> getVal();
    }
    int operator[](std::string str) const {
        for (int i = 0; i < sz; i++)
        if (data[i] -> hasKey(str)) {
            return data[i] -> getVal();
        }
        return 0;
    }
    int size();
    ~Map();
};