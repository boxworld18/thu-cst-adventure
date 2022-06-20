#include "Part.h"

Part::Part() {
    id = 0;
}

Part::Part(int num) {
    id = num;
}

int& Part::get() {
    return id;
}

