#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <memory>

template <typename T>
class Array {
private:
    std::unique_ptr<T*[]> data;
    size_t capacity;
    size_t size;

public:
    Array(size_t capacity) : size(0), capacity(capacity), data(new T*[capacity]) {
        for (size_t i=0; i<capacity; ++i){ data[i] = nullptr; }
    }
    ~Array(){
        ClearAll();
        delete[] data;
    }

    void Add(T* element){
        if (size >= capacity) { throw std::overflow_error("Array capacity exceeded"); }
    data[size++] = element;
    }
    T* Get(size_t index) const {
        if (index >= size) { throw std::out_of_range("Index out of bounds"); }
        return data[index];
    }
    size_t Size() const { return size; }
    size_t Capacity() const { return capacity; }
    void Clear(size_t index){
        if (index >= size) { throw std::out_of_range("Index out of bounds"); }
        delete data[index];
        for (size_t i=index; i<size-1; ++i){
            data[i] = data[i+1];
        }
        data[--size] = nullptr;
    }
    void ClearAll() {
        for (size_t i = 0; i < size; ++i) {
            delete data[i];
            data[i] = nullptr;
        }
        size = 0;
    }
};

#endif