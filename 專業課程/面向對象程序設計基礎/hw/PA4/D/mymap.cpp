#include "mymap.h"

void myMap::initialize(int capacity_){
    capacity = capacity_;
  
    size = 0;
    key_list_ = new string[capacity];
    value_list_ = new Node*[capacity];

    history_size = 0;
    history_value_list_ = new Node*[capacity];
}

void myMap::insert(const string &key, Node* value) {
    // 先看是否有同名节点，若有则替换之
    for (int i = 0; i < size; ++ i) {
        if (key==key_list_[i]) {
            value_list_[i] = value; 
            return;
        }
    } 

    // 若没有同名节点，则新建一个
    key_list_[size] = key;
    value_list_[size] = value;
    size += 1;

    // 存储历史信息
    history_value_list_[history_size++] = value;
}


Node* myMap::operator[](const string &key) {
    for (int i = 0; i < size; ++ i) {
        if (key==key_list_[i]) {
            return value_list_[i]; 
        }
    } 
    // 查找失败
	return nullptr;
}

myMap::~myMap() {    
    if(size) { 
        delete[] key_list_; 
        delete[] value_list_;

        // 析构出现过的节点
        for (int i = 0; i < history_size; ++ i) 
        	delete history_value_list_[i];	

        delete history_value_list_;
    }
}