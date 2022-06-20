#pragma once
#include "node.h"

//双目运算符基类
class OperationNodeTwo : public Node {
protected:
    //指向与运算符相连的操作数
    Node *input1, *input2;
public:
    OperationNodeTwo(string name, Node *x1, Node *x2) : Node(name), input1(x1), input2(x2) {}

    void calc() override;

    virtual ~OperationNodeTwo() = 0;

};

