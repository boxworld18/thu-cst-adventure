#include <iostream>
#include <cstdlib>
#include "Vector.h"
#include "Node.h"
#include <string>

using namespace std;

void test_equivalence(Vector & a, Vector & b, string msg){
	if(a.getlen() != b.getlen()){
		cout << msg << ": WRONG LEN" << endl;
		return;
	}
	for(int i = 0; i < a.getlen(); ++i){
		if(a[i] != b[i]){
			cout << msg << endl;
			cout << ": WRONG i: " << i << " A: " << a[i] << " B: " << b[i] << endl;
			return;
		}
	}
	cout << "pass" << endl;
}
 
void outputArray(Vector& a, int len){
	for(int i = 0; i < len - 1; i ++){
		cout << a[i] << " ";
	}
	cout << a[len - 1] << endl;
}

void readArray(Vector& a, int n)
{
	int value;
	for(int i = 0; i < n; i++)
	{
		cin >> value;
		a.append(value);
	}
}

Vector test1()
{
	int len, k, n;
	int p, q, r;

	cin >> len;
	Vector a(len);
	cin >> n;
	readArray(a, n);

	cin >> k;
	for (int i = 0; i < k; i ++){
		cin >> p;
		switch (p){
			case 0:
				cin >> q;
				a.append(q);
				break;
			case 1:
				cin >> q >> r;
				a.insert(q, r);
				break;
			case 2:
				cin >> q >> r;
				a.swap(q, r);
				break;
			case 3:
				a.dilatation();
				break;
			default:
				break;
		}
		outputArray(a, a.getlen());
	}
	Vector tmp(a);
	test_equivalence(a, tmp, "Wrong implementation of copy constructor");
	return tmp;
}

void test2(){
	Vector a(test1());
	outputArray(a, a.getlen());
	Vector b(1);
	if(b.getlen() != 0){
		cout << "Wrong implementation of constructor" << endl;
	}
	b = a;
	test_equivalence(a, b, "Wrong implementation of copy assignment operator");
	Vector c(1);
	c = move(a);
	if(a.getlen() != 0){
		cout << "Wrong implementation of move assignment operator" << endl;
	}
	outputArray(c, c.getlen());
}

int main()
{
	int ref_ans;
	cin >> ref_ans;
	test2();
	Node::outputResult(ref_ans);
	return 0;
}
