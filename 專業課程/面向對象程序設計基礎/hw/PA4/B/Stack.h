#ifndef __STACK
#define __STACK

#include "LinearDataStruct.h"
#include "IteratorBase.h"

class Stack: public LinearDataStruct {
    // TODO
public:

    class Iterator: public IteratorBase {
        int max_n;
        int* data_start;
    public:
        Iterator(int* _data, int _idx, int _max_n, int* _data_start): IteratorBase(_data, _idx) {
            max_n = _max_n;
            data_start = _data_start;
        }

        void operator++(int) {
            idx++;
            data++;
            if (idx == max_n) {
                idx = 0;
                data = data_start;
            }
        }
    };

    using LinearDataStruct::LinearDataStruct;

    void push(int num) {
        data[idx_end] = num;
        idx_end = (idx_end + 1) % max_n;
        n++;
    }

    int pop() {
        idx_end = (idx_end + max_n - 1) % max_n;
        int x = idx_end;
        n--;
        return data[x];
    }

    Iterator begin() {
        Stack::Iterator a(&data[(idx_begin + 1) % max_n], (idx_begin + 1) % max_n, max_n, &data[0]);
        std::cout << data[idx_begin] << " ";
        return a;
    }

    Iterator end() {
        Stack::Iterator a(&data[idx_end], idx_end, max_n, &data[0]);
        return a;
    }

    // TODO
};


#endif 
