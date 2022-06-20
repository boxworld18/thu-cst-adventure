#pragma once
#include "operation.h"

class OperatorMinus: public OperationNodeTwo {
public:
    OperatorMinus(string name, Node *x1, Node *x2): OperationNodeTwo(name, x1, x2) {};
    void UpdateValue();
    ~OperatorMinus() {};
};

class OperatorPlus: public OperationNodeTwo {
public:
    OperatorPlus(string name, Node *x1, Node *x2): OperationNodeTwo(name, x1, x2) {};
    void UpdateValue();
    ~OperatorPlus() {};
};

