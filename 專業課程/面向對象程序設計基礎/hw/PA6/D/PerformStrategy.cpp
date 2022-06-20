#include "PerformStrategy.h"

PerformStrategy::PerformStrategy(double _perform): perform(_perform) {
    
}

int sPerformStrategy::getTotal(int base) {
    return base + 1000;
}

int mPerformStrategy::getTotal(int base) {
    return base * 0.1 * (1.0 + perform) * 10;
}

int lPerformStrategy::getTotal(int base) {
    return base * 0.1 * (1.0 + perform * 2.0) * 10;
}