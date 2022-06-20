#pragma once

class Alien: public WhatCanMotion, public WhatCanSpeak {
    string name;
    int x, y;
public:
    Alien(string _name) {
        name = _name;
        x = 0;
    }
    void speak() {
        x = 1;
        std::cout << name << " is speaking\n";
    }
    void motion() {
        std::cout << name << " is moving\n";
    }
    void stop() {
        y = 1;
        std::cout << name << " stops\n";
    }
    ~Alien() = default;
};