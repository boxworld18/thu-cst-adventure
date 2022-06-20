// test.c
#include <iostream>
using namespace std;

#if defined(__F1__)
#include "f1.h"
#endif
#if defined(__F2__)
#include "f2.h"
#endif
#if defined(__F3__)
#include "f3.h"
#endif
#if defined(__F4__)
#include "f4.h"
#endif

int main(int argc, const char *argv[])
{
    int a = 3, b = 7;

#if defined(__F1__)
    cout << f1(a, b) << endl;
#endif
#if defined(__F2__)
    cout << f2(a, b) << endl;
#endif
#if defined(__F3__)
    cout << f3(a, b) << endl;
#endif
#if defined(__F4__)
    cout << f4(a, b) << endl;
#endif
    return 0;
}