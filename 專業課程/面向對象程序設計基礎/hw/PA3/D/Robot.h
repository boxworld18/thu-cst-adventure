#pragma once
#include "Part.h"
#include <iostream>
#include <string>

class Robot{
    int needParts, countParts;
    Part* parts;
public:
    std::string type;
    Robot();
    Robot(int num);
    bool is_full();
    void add_part(Part);
    int run();
    int& getNeedParts();
    int& getCountParts();
    int& getPartId(int);
    friend std::ostream& operator<<(std::ostream& out, const Robot& src);
    virtual ~Robot();
};