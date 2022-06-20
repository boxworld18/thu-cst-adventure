#pragma once
#include <list>
#include <iostream>
#include <memory>
#include "CustomClass.h"
class Object;
class Content {
public:
	virtual Content& operator+=(const int& _x) {
		return *this;
	}
	
	virtual Content& operator+=(const std::string& _x) {
		return *this;
	}

	virtual Object& get(const int& _x) {
	}

	virtual void output(std::ostream& out){ //virtual function for output
		std::cout << "the operator is not supported for this type." << std::endl;
	}
};

class IntContent: public Content {
private:
	int x;
public:
	IntContent(int _x): x(_x) {

	}

	void output(std::ostream& out){
		out << x;
	}

	IntContent& operator+=(const int& _x) {
		x += _x;
		return *this;
	}
};

class StringContent: public Content {
private:
	std::string x;
public:
	StringContent(std::string _x): x(_x) {

	}

	void output(std::ostream& out){
		out << x;
	}

	StringContent& operator+=(const std::string& _x) {
		x += _x;
		return *this;
	}
};

class VectorContent: public Content {
private:
 	std::vector<Object> x; 
public:
 	VectorContent(const std::vector<Object>& _x): x(_x) {

	}
	Object& get(const int& _x) {
		return x[_x];
	}
};

class CustomContent: public Content {
private:
	CustomClass x;
public:
	CustomContent(const CustomClass& _x): x(_x) {

	}
};

class Object {
private:
	std::shared_ptr<Content> pt;
public:
	Object() {

	}

	Object(int x) {
		pt = std::make_shared<IntContent>(IntContent(x));
	}

	Object(const std::string &x){
		pt = std::make_shared<StringContent>(StringContent(x));
	}

	Object(const std::vector<Object> &x){
		pt = std::make_shared<VectorContent>(VectorContent(x));
	}
	
	Object(const CustomClass &x){
		pt = std::make_shared<CustomContent>(CustomContent(x));
	}

	friend std::ostream& operator<<(std::ostream& out, const Object& obj) {
		obj.pt->output(out);
		return out;
	}

	Object& operator+=(const int& y){
		pt->operator+=(y);
		return *this;
	}

	Object& operator+=(const std::string &y){
		pt->operator+=(y);
		return *this;
	}

	Object& operator=(const int &x) {
		pt = std::make_shared<IntContent>(IntContent(x));
		return *this;
	}

	Object& operator=(const std::string &x) {
		pt = std::make_shared<StringContent>(StringContent(x));
		return *this;
	}

	Object& operator[](const int& x) {
		return pt->get(x);
	}
	~Object() {
		
	}

};
