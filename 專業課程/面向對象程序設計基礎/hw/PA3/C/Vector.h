#pragma once
#include "Node.h"
#include <iostream>

class Vector {
private:
	int capacity;
	int len;
	Node* array;
public:
	Vector(int n);
	~Vector();
	Vector(const Vector & other);
	Vector(Vector && other);
	Vector & operator=(const Vector & other);
	Vector & operator=(Vector && other);
	Node& operator [] (int pos);
	void append(int value);
	void insert(int pos, int value);
	void swap(int pos1, int pos2);
	void dilatation();
	int getlen();
}; 