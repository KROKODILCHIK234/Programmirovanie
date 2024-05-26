#include "vector.h"


// С заданным размером
Vector::Vector(int startCapacity)
{
    if (startCapacity <= 0 or startCapacity >= maxSize)
        capacity = DEFAULT_CAPACITY;
    else
        capacity = startCapacity;
    ptr = new int[capacity];
    size = 0;
}


// С заданным размером и наполнением
Vector::Vector(int initialSize, int initialValue)
{
    if (initialSize <= 0 or initialSize >= maxSize)
        capacity = DEFAULT_CAPACITY;
    else
        capacity = initialSize;

    size = initialSize;
    ptr = new int[capacity];

    for (int i=0; i < size; i++)
        ptr[i] = initialValue;
}

// Деструктор
Vector::~Vector() {
    delete[] ptr;
}

// Копирование
Vector::Vector(const Vector &arr){
    ptr = new int[arr.capacity];
    size = arr.size;
    capacity = arr.capacity;
    for (int i=0; i < size; i++)
        ptr[i] = arr.ptr[i];
}


// Присваивание
Vector& Vector::operator =(const Vector& arr)
{
    if (this == &arr)
        return *this;

    if (capacity != arr.capacity){
        delete[] ptr;
        ptr = new int[arr.capacity];
        capacity = arr.capacity;
    }

    size = arr.size;
    for (int i=0; i<size; i++)
        ptr[i] = arr.ptr[i];
    return *this;
}


// Операторы сравнения
bool Vector::operator ==(const Vector& other) const {
    if (size != other.size) {
        return false;
    }

    for (int i = 0; i < size; ++i) {
        if (ptr[i] != other.ptr[i]) {
            return false;
        }
    }

    return true;
}

bool Vector::operator !=(const Vector& other) const {
    return !(*this == other);
}


int& Vector::operator [](int index)
{
    if (index >= size || index < 0)
        throw ArrayException();
    else
        return ptr[index];
}





int Vector::getSize() {
    return size;
}
int Vector::getCapacity() {
    return capacity;
}



bool Vector::isEmpty() {
    if (size == 0)
        return true;
    else
        return false;
}

void Vector::clear(){
    if (!isEmpty()){
        delete[] ptr;
        // Устанавливаем указатель на nullptr
        ptr = nullptr;
        size = 0;
        capacity = 0;
    }
}

void Vector::increaseCapacity(int newCapacity){
    capacity = newCapacity < capacity*2 ?
               capacity*2 : newCapacity;
    int* newPtr = new int[capacity];
    for (int i=0; i < size; i++)
        newPtr[i]=ptr[i];
    delete[] ptr;
    ptr = newPtr;
}


void Vector::push_back(int element){
    if (size == capacity)
        increaseCapacity(size+1);

    ptr[size] = element;
    size++;
}

void Vector::pop_back(){
    ptr[size-1] = 0;
    size--;
}

void Vector::remove(int index){
    if (index < 0 || index >= size)
        throw ArrayException();
    for (int j=index; j < size-1; j++)
        ptr[j] = ptr[j+1];
    ptr[size-1] = 0;
    size--;
}






ostream& operator <<(ostream& out, const Vector& v){
    out << "Total size: "<< v.size << endl;
    for (int i=0; i < v.size; i++)
        out << v.ptr[i] << endl;
    return out;
}
