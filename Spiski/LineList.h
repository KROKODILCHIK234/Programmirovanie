#ifndef LINELIST_H
#define LINELIST_H

#include "../vector/vector.h" // Подключаем определение класса Vector

#include <iostream>

class CircularBuffer {
private:
    int* buffer; // указатель на массив элементов буфера
    int head; // индекс начала буфера
    int size; // размер буфера

public:
    CircularBuffer(int n) : head(0), size(n) { // конструктор класса с параметром размера буфера
        buffer = new int[n]; // выделяем память под массив элементов размера n
        for (int i = 0; i < n; ++i) {
            buffer[i] = i + 1; // заполняем буфер последовательными числами от 1 до n
        }
    }

    ~CircularBuffer() { // деструктор класса
        delete[] buffer; // освобождаем память, выделенную под массив buffer
    }

    void remove(int index) { // метод удаления элемента с указанным индексом
        buffer[index] = -1; // заменяем элемент на -1, обозначая его удаление
    }

    int next(int index, int step) { // метод определения индекса следующего элемента на указанном шаге от текущего индекса
        for (int i = 0; i < step; ++i) {
            do {
                index = (index + 1) % size; // находим следующий индекс, учитывая замаскированное удаление элементов
            } while (buffer[index] == -1); // пропускаем удаленные элементы
        }
        return index; // возвращаем индекс следующего элемента
    }

    void display() const { // метод отображения содержимого буфера
        for (int i = 0; i < size; ++i) {
            if (buffer[i] != -1) { // выводим элемент, если он не удален
                std::cout << buffer[i] << " "; // выводим элемент через пробел
            }
        }
        std::cout << std::endl; // переход на новую строку
    }
};

#endif // LINELIST_H
