#include <iostream>
#include <vector>
using namespace std;
Class OuOb {
    int x;
};

void add(OuOb* x, vector<OuOb>& vec) {
    vec.push_back(*x);
    // (1)
}

int main() {
    OuOb *x = new OuOb;
    vector<OuOb> v;
    add(x, v);
    delete x;
}