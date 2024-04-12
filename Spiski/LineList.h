#ifndef LINELIST_H
#define LINELIST_H
 
#include "../vector/vector.h" // Подключаем определение класса Vector
 
#include <iostream>
 
class CircularBuffer {
private:
    int* buffer;
    int head;
    int size;
 
public:
    CircularBuffer(int n) : head(0), size(n) {
        buffer = new int[n];
        for (int i = 0; i < n; ++i) {
            buffer[i] = i + 1;
        }
    }
 
    ~CircularBuffer() {
        delete[] buffer;
    }
 
    void remove(int index) {
        buffer[index] = -1;
    }
 
    int next(int index, int step) {
        for (int i = 0; i < step; ++i) {
            do {
                index = (index + 1) % size;
            } while (buffer[index] == -1);
        }
        return index;
    }
 
    void display() const {
        for (int i = 0; i < size; ++i) {
            if (buffer[i] != -1) {
                std::cout << buffer[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};
 
 
 
#endif // LINELIST_H
