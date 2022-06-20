#include "Bob.h"

int Bob::run() {
    int tmp = 0;
    for (int i = 0; i < getCountParts(); i++) {
        int id = getPartId(i);
        tmp += id * id;
    }
    return tmp;
}