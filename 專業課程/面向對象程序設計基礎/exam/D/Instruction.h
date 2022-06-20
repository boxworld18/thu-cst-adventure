#pragma once
#include <vector>
#include "MagicArray.h"

class Instruction
{
public:
    int size, count;
    Op op[1010];
    vector<Instruction*> vec;

    void apply(std::vector<int> &vec) {
        for (int i = 0; i < count; i++)
        vec[op[i].id] += int(op[i].val);
    }
    void apply(std::vector<double> &vec) {
        for (int i = 0; i < count; i++)
        vec[op[i].id] += op[i].val;
    }

    std::vector<Instruction*>& getInstructions() {
        return vec;
    }
};

