#include "Map.h"

Map::Map(int n) {
    for (int i = 0; i < n; i++) data[i] = new Pair();
    sz = 0;
}

int Map::size() {
    return sz;
}

Map::~Map() {
    while (Pair::n_create > Pair::n_free) delete data[Pair::n_free];
    sz = 0;
}
