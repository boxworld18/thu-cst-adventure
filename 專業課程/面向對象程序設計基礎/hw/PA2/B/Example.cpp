#include <iostream>
#include "Example.h"

using namespace std;

	// (2)
int Example::totalCase = 0;

Example::Example(int data) {
	// (3)
	ID = ++totalCase;
	cout << "Example #" << ID << " is created" << endl;
	num = data;
}

void Example::getData() {
	// (4)
	cout << "The data of Example #" << ID << " is " << num << endl;
}

Example::~Example() {
	// (5)
	cout << "Example #" << ID << " is destroyed" << endl;
}