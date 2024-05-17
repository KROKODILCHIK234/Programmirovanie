#pragma once

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <iostream>

using namespace std;


class ArrayException{
    void f(int k, int index, int size) {
        try {
            int res = g(k, index, size);
        } catch (ArrayException &e) {
            cout << "Произошла ошибка!!" << endl;
        }
    }
    int g(int n, int index, int size){
        if (index < 0 || index >= size)
            throw ArrayException();
        else
            return n+1;
    }
};



const int DEFAULT_CAPACITY = 10;
const int DEFAULT_MAX_SIZE = 10;

class Vector {
private:
    int* ptr;
    int size;
    int maxSize = DEFAULT_MAX_SIZE;
    int capacity;

public:
    explicit Vector(int startCapacity=DEFAULT_CAPACITY);
    Vector(int initialSize, int initialValue);
    ~Vector();
    Vector(const Vector &arr);

    Vector& operator =(const Vector& arr);
    bool operator ==(const Vector& other) const;
    bool operator !=(const Vector& other) const;
    int& operator [](int index);

    int getSize();
    int getCapacity();

    bool isEmpty();
    void clear();

    void increaseCapacity(int newCapacity);
    void push_back(int element);
    void pop_back();
    void remove(int index);


    friend ostream& operator <<(ostream& out, const Vector& arr);
};


#endif //VECTOR_VECTOR_H
