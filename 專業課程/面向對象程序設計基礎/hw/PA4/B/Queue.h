#ifndef __QUEUE
#define __QUEUE

#include "LinearDataStruct.h"
#include "IteratorBase.h"

class Queue: public LinearDataStruct {
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
            if (idx == max_n - 1) {
                idx = 0;
                data = data_start;
            } else {
                idx++;
                data++;
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
        int x = idx_begin;
        idx_begin = (idx_begin + 1) % max_n;
        n--;
        return data[x];
    }

    Iterator begin() {
        Queue::Iterator a(&data[(idx_begin + 1) % max_n], (idx_begin + 1) % max_n, max_n, &data[0]);
        std::cout << data[idx_begin] << " ";
        return a;
    }

    Iterator end() {
        Queue::Iterator a(&data[idx_end], idx_end, max_n, &data[0]);
        return a;
    }
    // TODO
};

#endif 
