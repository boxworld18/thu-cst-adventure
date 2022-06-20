#pragma once
#include <string>
#include <iostream>

class Animal {
private:
	std::string name, type;
public:
    Animal(const std::string &_name, const std::string &_type): name(_name), type(_type) {}

    //Cannot copy animals
    Animal(const Animal &other) = delete;
    //Can move animals
    Animal(Animal &&other): name(other.name), type(other.type) {
        other.name = ""; other.type = "empty";
    }

    //Cannot copy animals
    Animal& operator=(const Animal &other) = delete;
    //Can move animals
    Animal& operator=(Animal &&other){
        if(type != "empty"){
            std::cout << "There has already been an animal here. Cannot move." << std::endl;
        }
        name = other.name; type = other.type;
        other.name = ""; other.type = "empty";
		return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Animal& animal){
        out << animal.type << " " << animal.name;
		return out;
    }

    //pure virtual destruction
    virtual ~Animal()=0;
};

inline Animal::~Animal()
{
    if(type != "empty"){
        std::cout << "An animal deleted." << std::endl;
    }
}

class Dog: public Animal {
public:
    Dog(const std::string &_name): Animal(_name, "dog") {};
};

class Bird: public Animal {
public:
    Bird(const std::string &_name): Animal(_name, "bird") {};
};