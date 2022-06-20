#include "operation.h"

OperationNodeTwo::~OperationNodeTwo() = default;

void OperationNodeTwo::calc() {
	// 递归计算
    input1->calc();		
    input2->calc();		
	// 更新当前节点值 (根据input1和input2的value进行加法/减法)
    UpdateValue();		
}
