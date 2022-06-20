#pragma once
#include <string>
#include <iostream>
#include "node.h"
#include "operation.h"
#include "mymap.h"

using std::string;
using std::cout;
using std::setprecision;
using std::endl;


// Graph类实现对计算图节点的管理以及计算操作的记录
class Graph {
private:
    // 管理计算图中的所有结点，同名节点仅保留最新版本，使用nodes->insert(key, value)增加节点
    myMap nodes_;

public:
    Graph(int num_node);

    //禁止默认拷贝构造，防止重复delete
    Graph(const Graph &) = delete;

    //禁止默认赋值，防止重复delete
    void operator=(const Graph &) = delete;

    //插入placeholder
    void InsertPlaceholder(const string &node_name);

    //插入constant
    void InsertConstant(const string &node_name, float value);

    //插入二元运算符结点
    void InsertOperation(const string &node_name, const string &operation_type, 
                            const string &input1, const string &input2);

    //进行EVAL操作 输入待EVAL的节点名称 以及placeholder的初始化列表
    void Eval(const string &node_name, const int &argument_num, 
                const string* argument_name_list_, const float* argument_value_list_);

    ~Graph();
};
