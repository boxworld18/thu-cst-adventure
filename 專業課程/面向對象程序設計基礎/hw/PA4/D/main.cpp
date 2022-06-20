#include <iostream>
#include <string>
#include <cstdio>
#include "graph.h"

using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    // 最多产生n+m个节点
    Graph tf(n+m);

    for (int i = 0; i < n; ++i) {
        string node_name, node_type;
        cin >> node_name >> node_type;    //读入变量信息
        if (node_type == "P") tf.InsertPlaceholder(node_name);
        else if (node_type == "C") {
            float value;
            cin >> value;
            tf.InsertConstant(node_name, value);
        }
    }

    for (int i = 0; i < m; ++i) {        //读入结点信息
        string node_name, _, operation, left, right;
        cin >> node_name >> _ >> left >> operation >> right;
        tf.InsertOperation(node_name, operation, left, right);

    }

    for (int i = 0; i < q; ++i) {        //读入操作信息
        string op;
        cin >> op;
        if (op == "EVAL") {
            string node_name;
            int argument_num;

            cin >> node_name;
            cin >> argument_num;

            string* argument_name_list_ = new string[argument_num];
            float* argument_value_list_ = new float[argument_num];
 
            for (int j = 0; j < argument_num; ++ j) {
                cin >> argument_name_list_[j] >> argument_value_list_[j];
            }
 
            tf.Eval(node_name, argument_num, argument_name_list_, argument_value_list_);
 
            delete[] argument_name_list_;
            delete[] argument_value_list_;
        }
    }
    return 0;
}
