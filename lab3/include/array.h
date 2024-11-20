#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <memory>

template <typename T>
class Array {
private:
    std::unique_ptr<std::unique_ptr<T>[]> data;
    size_t capacity;
    size_t size;

public:
    Array(size_t capacity) : capacity(capacity), size(0) {
        data = std::make_unique<std::unique_ptr<T>[]>(capacity);
        for (size_t i=0; i<capacity; ++i){ data[i] = nullptr; }
    }
    ~Array() = default;

    void Add(std::unique_ptr<T> element){
        if (size >= capacity) { throw std::overflow_error("Array capacity exceeded"); }
        data[size++] = std::move(element);
    }
    T* Get(size_t index) const {
        if (index >= size) { throw std::out_of_range("Index out of bounds"); }
        return data[index].get();
    }
    size_t Size() const { return size; }
    size_t Capacity() const { return capacity; }
    void Clear(size_t index){
        if (index >= size) { throw std::out_of_range("Index out of bounds"); }
        data[index].reset();
        for (size_t i=index; i<size-1; ++i){
            data[i] = std::move(data[i+1]);
        }
        data[--size] = nullptr;
    }
    void ClearAll() {
        for (size_t i = 0; i < size; ++i) {
            data[i].reset();
            data[i] = nullptr;
        }
        size = 0;
    }
};

#endif