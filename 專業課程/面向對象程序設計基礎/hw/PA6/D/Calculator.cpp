#include "Calculator.h"

Calculator::Calculator(LevelStrategy* _ls, PerformStrategy* _ps): ls(_ls), ps(_ps) {

}

int Calculator::get_base() {
    return ls->getBase();
}

int Calculator::get_total(int base) {
    return ps->getTotal(base);
}

Calculator::~Calculator() {

}