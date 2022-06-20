#pragma once

#include <string>
#include <iostream>
#include <iomanip>

using std::string;

//Node类 为所有节点的基类

class Node {
protected:
    //结点数值
    float value_;

    //结点名字
    string name_;

public:
    Node(string _name, float _value = 0) : name_(_name), value_(_value) {}

    //interface of value_
    inline float value() { return value_; }

    //interface if name_
    inline string name() { return name_; }

    // 节点调用子节点的计算，之后更新自身值的操作
    virtual void calc() {}

    // 节点通过子节点更新value_的方法
    virtual void UpdateValue() {}

    virtual ~Node() = 0;

};


class PlaceholderNode : public Node {
public:
    PlaceholderNode(string name) : Node(name) {}
    void set_val(float val);
    void calc() override;
};



class ConstantNode : public Node {
public:
    ConstantNode(string name, float value) : Node(name, value) {}
};