#include "Vector.h"

Vector::Vector(int n) {
    capacity = n;
    len = 0;
    array = new Node[capacity];
}

Vector::~Vector() {
    if (array != nullptr) delete[] array;
    array = nullptr;
    len = 0;
    capacity = 0;
}

Vector::Vector(const Vector & other) {
    len = other.len;
    capacity = other.capacity;
    
    array = new Node[capacity];
    std::copy(other.array, other.array + other.len, array);
}

Vector::Vector(Vector && other) {
    len = other.len;
    capacity = other.capacity;
    array = other.array;
    
    other.array = nullptr;
    other.len = 0;
    other.capacity = 0;
}
	
Vector& Vector::operator=(const Vector & other) {
    delete[] array;
    
    len = other.len;
    capacity = other.capacity;

    array = new Node[capacity];
    std::copy(other.array, other.array + other.len, array);
    
    return *this;
}


Vector& Vector::operator=(Vector && other) {
    delete[] array;
  
    array = other.array;
    len = other.len;
    capacity = other.capacity;
    
    other.array = nullptr;
    other.len = 0;
    other.capacity = 0;
    
    return *this;
}
	
Node& Vector::operator[](int pos) {
    return array[pos];
}
	
void Vector::append(int value) {
    array[len] = value;
    len++;
}

void Vector::insert(int pos, int value) {
    for (int i = len; i > pos; i--) {
        array[i] = std::move(array[i - 1]);
    }
    len++;
    array[pos] = value;
}

void Vector::swap(int pos1, int pos2) {
    Node p = std::move(array[pos1]);
    array[pos1] = std::move(array[pos2]);
    array[pos2] = std::move(p);
}

void Vector::dilatation() {
    Node *array2 = array;
    array = nullptr;

    capacity *= 2;
    array = new Node[capacity];
    for (int i = 0; i < len; i++) array[i] = std::move(array2[i]);
    delete[] array2;
}

int Vector::getlen() {
    return len;
}
