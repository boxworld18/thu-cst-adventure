#pragma once
#include <string>
#include <map>
#include <iostream>

class CustomClass
{
private:
    std::string name;
    static std::map<std::string, int> cnt;
public:
    CustomClass(const std::string &_name): name(_name) {
        cnt[name] += 1;
        // std::cout << name << " created" << std::endl;
    }
    CustomClass(const CustomClass &other): name(other.name) {
        cnt[name] += 1;
        // std::cout << name << " created" << std::endl;
    }
    ~CustomClass(){
        cnt[name] -= 1;
        // std::cout << name << " deleted" << std::endl;
    }

    static void detect_leak(){
        for(auto &k : cnt) {
            if(k.second){
                std::cout << "memory leak detected: " << k.first << std::endl;
            }
        }
    }
};