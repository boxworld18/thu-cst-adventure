#include <string>
#include "Cow.h"
using namespace std;

Cow::Cow(string name1, int l1, int u1, int m1) {
    name = name1;
    l = l1;
    u = u1;
    m = m1;
    vol = 0;
    stat = 0;
}

Cow::Cow(){
    vol = 0;
    stat = 0;
}