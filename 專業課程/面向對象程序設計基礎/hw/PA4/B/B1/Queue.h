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
        Iterator(int* _data, int _idx, int* _data_start, int _max_n): IteratorBase(_data, _idx) {
            data_start = _data_start;
            max_n = _max_n;
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
        int x = idx_begin;
        idx_begin = (idx_begin + 1) % max_n;
        n--;
        return data[x];
    }

    Iterator begin() {
        std::cout << data[idx_begin] << " ";
        Queue::Iterator a(&data[idx_begin], idx_begin, &data[idx_begin], max_n);
        a++;
        return a;
    }

    Iterator end() {
        Queue::Iterator a(&data[idx_end], idx_end, &data[idx_begin], max_n);
        return a;
    }
    // TODO
};

#endif 
