#pragma once
#include "Robot.h"

class Alice: public Robot{
public:
    Alice(): Robot() {
        type = "Alice";
    }
    Alice(int num): Robot(num) {
        type = "Alice";
    }
};