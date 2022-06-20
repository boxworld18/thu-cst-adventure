#pragma once
#include "Instruction.h"
#include <iostream>
using namespace std;

class Op {
public:
    int id;
    double val;
    string type;

    Op() {

    }

    void output() {
        cout << "arr[" << id << "]" << type << val << endl;
    }
};

class MagicArray: public Instruction {
public:
    
    MagicArray() {}
    MagicArray(int n) {}

    double& operator[](int i) {
        op[count].id = i;
        op[count].type = " += ";
        return op[count++].val;
    }

    void output() {
        for (int i = 0; i < count; i++) op[i].output();
    }
};