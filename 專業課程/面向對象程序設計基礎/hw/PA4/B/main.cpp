#include <iostream>
#include "LinearDataStruct.h"
#include "Stack.h"
#include "Queue.h"

int main() {
    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);

    LinearDataStruct* lds[10];
    int type[10] = {0};

    int m = 0;
    std::cin >> m;

    for (int i = 0; i < m; ++i) {
        int op;
        int s;
        std::cin >> op >> s;

        if (op == 0) {
           lds[i] = new Stack(s);
           type[i] = 0;
        }
        else {
            lds[i] = new Queue(s);
            type[i] = 1;
        }
    }


    int k;
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        int op;
        int idx;
        std::cin >> op >> idx;
        if (op == 0) {
            int c;
            std::cin >> c;
            if (lds[idx]->size() >= lds[idx]->max_size()) {
                std::cout << "Full!" << std::endl;
            }
            else {
                lds[idx]->push(c);
            }
        }
        else if (op == 1) {
            if (lds[idx]->size() == 0) {
                std::cout << "Empty!" << std::endl;
            }
            else {
                std::cout << lds[idx]->pop() << std::endl;
            }
        }
        else if (op == 2) {
            std::cout << lds[idx]->max_size() << std::endl;
        }
        else if (op == 3) {
            std::cout << lds[idx]->size() << std::endl;
        }
        else {
            if (lds[idx]->size() == 0) {
                std::cout << "Empty!" << std::endl;
            }
            else {
                if (type[idx] == 0) {
                    Stack* S = dynamic_cast<Stack*>(lds[idx]);
                    for (Stack::Iterator it = S->begin(); it != S->end(); it++) {
                        std::cout << *it << " ";
                    }
                }
                else {
                    Queue* Q = dynamic_cast<Queue*>(lds[idx]);
                    for (Queue::Iterator it = Q->begin(); it != Q->end(); it++) {
                        std::cout << *it << " ";
                    }
                }

                std::cout << std::endl;
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        delete lds[i];
    }

    return 0;
}
