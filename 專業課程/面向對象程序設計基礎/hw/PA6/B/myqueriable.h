#pragma once
#include <functional>

template <class T> 
class MyQueriable {
    T container;
    int _size;
public:
    MyQueriable() {

    }

    MyQueriable(T _container) {
        container = _container;
        _size = _container.size();
    }
    
    int size() {
        return _size;
    }

    template<class fT>
    MyQueriable where(fT f) {
        T a;
        for (auto i : container) {
            if (f(i)) a.push_back(i);
        }
        MyQueriable b(a);
        return b;
    }

    template<class fT>
    MyQueriable apply(fT f) {
        T a;
        for (auto i : container) {
            a.push_back(f(i));
        }
        MyQueriable b(a);
        return b;
    }

    auto sum() {
        auto ans = *container.begin();
        ans = 0;
        for (auto i : container) ans += i;
        return ans;
    }

    auto operator[](int x) {
        int count = 0;
        for (auto i : container) {
            if (count == x) return i;
            count++;
        }
    }
};

template <class T>
MyQueriable<T> from(T a) {
    MyQueriable<T> b(a);
    return b;
}