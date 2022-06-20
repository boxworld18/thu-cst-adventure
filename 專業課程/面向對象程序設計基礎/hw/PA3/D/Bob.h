#pragma once
#include "Robot.h"

class Bob: public Robot{
public:
    Bob(): Robot() {
        type = "Bob";
    }
    Bob(int num): Robot(num) {
        type = "Bob";
    }
    int run();
};