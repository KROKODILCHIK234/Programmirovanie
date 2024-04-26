#ifndef RATIONAL_VECTOR_H
#define RATIONAL_VECTOR_H

#include <iostream>
#include <algorithm>

template<typename T>
class Vector {
private:
    T* array; // Указатель на первый элемент массива
    size_t capacity; // Размер выделенной памяти
    size_t size; // Текущий размер вектора

public:
    // Конструктор по умолчанию
    Vector() : array(nullptr), capacity(0), size(0) {}

    // Конструктор с заданным начальным размером
    Vector(size_t initial_size) : array(new T[initial_size]), capacity(initial_size), size(initial_size) {}

    // Деструктор
    ~Vector() {
        delete[] array;
    }

    // Метод добавления элемента в конец вектора
    void push_back(const T& value) {
        // Если массив уже заполнен, увеличиваем его размер вдвое
        if (size >= capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        array[size++] = value;
    }

    // Метод удаления элемента из указанной позиции
    void erase(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        // Сдвигаем элементы влево начиная с индекса до конца массива
        for (size_t i = index; i < size - 1; ++i) {
            array[i] = array[i + 1];
        }
        --size;
    }

    // Метод добавления элемента в указанную позицию
    void insert(size_t index, const T& value) {
        if (index > size) {
            throw std::out_of_range("Index out of range");
        }

        // Если массив уже заполнен, увеличиваем его размер вдвое
        if (size >= capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }

        // Сдвигаем элементы вправо начиная с конца массива до индекса
        for (size_t i = size; i > index; --i) {
            array[i] = array[i - 1];
        }
        array[index] = value;
        ++size;
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        return *(array + index);
    }

    // Метод получения размера вектора
    size_t getSize() const {
        return size;
    }

    // Метод выделения памяти для вектора
    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity) {
            return;
        }
        T* new_array = new T[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_array[i] = std::move(array[i]);
        }
        delete[] array;
        array = new_array;
        capacity = new_capacity;
    }

    // Оператор вывода для класса Vector
    friend std::ostream& operator<<(std::ostream& out, const Vector<T>& vec) {
        out << "[";
        for (size_t i = 0; i < vec.size; ++i) {
            out << vec.array[i];
            if (i != vec.size - 1) {
                out << ", ";
            }
        }
        out << "]";
        return out;
    }
};

#endif // RATIONAL_VECTOR_H
