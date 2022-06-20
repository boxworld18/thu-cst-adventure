#ifndef __ITERATORBASE
#define __ITERATORBASE

class IteratorBase {
    
protected:
    int* data;
    int idx;

public:

    IteratorBase(int* _data, int _idx): data(_data), idx(_idx) {

    }

    bool operator!=(const IteratorBase& iterator) {
        return idx != iterator.idx;
    }

    int& operator*() const {
        return *data;
    }

    virtual void operator++(int) {
        idx++;
        data++;
    }
    
    // TODO

};


#endif
