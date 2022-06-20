#pragma once
#include <string>
#include "node.h"

using std::string;

// 通过string关键字查询Node*
class myMap {
public:
    myMap() = default;

    // 初始化存储数组的大小
    void initialize(int capacity_);

    // 插入操作
    void insert(const string &key, Node* value);

    // 重载下标号实现查找操作
    Node* operator[](const string &key);

    ~myMap();

private:
    int capacity, size = 0, history_size;
    string* key_list_;
    Node** value_list_;

    // 存储所有历史节点，在析构时使用
    Node** history_value_list_;

};
