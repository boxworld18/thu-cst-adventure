#pragma once

class LevelStrategy {
public:
    virtual int getBase() = 0;
};

class P1LStrategy: public LevelStrategy {
public:
    int getBase();
};

class P2LStrategy: public LevelStrategy {
public:
    int getBase();
};

class P3LStrategy: public LevelStrategy {
public:
    int getBase();
};