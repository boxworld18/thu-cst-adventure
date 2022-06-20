#include "node.h"

Node::~Node() = default;

void PlaceholderNode::set_val(float val) {
    value_ = val;
}

void PlaceholderNode::calc() {
    
}
