#include "Test.h"

Test f1(Test a) {
    a.print("a");
    return a;
}

Test& f2(Test& a) {
    a.print("b");
    return a;
}

void f3(Test& a, Test& b) {
    Test c = std::move(a);
    a = std::move(b);
    b = std::move(c);
} 