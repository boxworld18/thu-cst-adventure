#include "calculate.h"

void OperatorPlus::UpdateValue() {
    value_ = input1->value() + input2->value();
}

void OperatorMinus::UpdateValue() {
    value_ = input1->value() - input2->value();
}