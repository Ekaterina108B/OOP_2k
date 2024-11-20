#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class Array {
private:
    std::unique_ptr<T[]> data;
    size_t capacity;
    size_t size;

    void Resize(size_t new_capacity) {
        auto new_data = std::unique_ptr<T[]>(new T[new_capacity]);
        for (size_t i=0; i<size; ++i){ new_data[i] = std::move(data[i]); }
        for (size_t i=size; i<new_capacity; ++i){ new_data[i] = nullptr; }
        data = std::move(new_data);
        capacity = new_capacity;
    }

public:
    Array() : data(nullptr), capacity(0), size(0) {}
    Array(size_t capacity) : capacity(capacity), size(0) {
        data = std::unique_ptr<T[]>(capacity);
        for (size_t i=0; i<capacity; ++i) { data[i] = nullptr; }
    }
    ~Array() = default;

    void Add(T element){
        if (size >= capacity) { Resize(capacity == 0 ? 1 : capacity*2); }
        data[size++] = std::move(element);
    }
    T& Get(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }
    T& GetEnd() const { return data[size-1]; }

    size_t Size() const { return size; }
    size_t Capacity() const { return capacity; }

    void Clear(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        data[--size] = nullptr;
    }
    void Reset() {
        for (size_t i = 0; i < size; ++i) {
            data[i] = nullptr;
        }
        size = 0;
        capacity = 0;
    }
};