#include "array.h"

Array::Array() : data(nullptr), size(0) {}

Array::Array(const size_t &n, unsigned char t = 0) : size(n) {
    if (n > 0) {
        data = new unsigned char[n];
        for (size_t i=0; i<n; ++i) { data[i] = t; }
    } else {
        data = nullptr;
    }
}

Array::Array(const std::initializer_list<unsigned char> &t) : size(t.size()) {
    data = new unsigned char[size];
    std::copy(t.begin(), t.end(), data);
}

Array::Array(const std::string &t) : size(t.length()){
    data = new unsigned char[size];
    for (size_t i = 0; i<size; ++i){ data[i] = static_cast<unsigned char>(t[i] - '0'); }
}

Array::Array(const Array &other) : data(other.data), size(other.size) {}

Array::Array(Array&& other) noexcept : data(other.data), size(other.size) {
    other.data = nullptr;
    other.size = 0;
}

Array& Array::operator=(const Array &other) {
    if (this != &other) {
        delete[] data;
    }
    size = other.size;
    data = new unsigned char[size];
    for (size_t i = 0; i<size; ++i) { data[i] = other.data[i]; }
    return *this;
}

Array::~Array() noexcept {
    delete[] data;
    size = 0;
}

size_t Array::GetSize(void) const{
    return size;
}

unsigned char Array::GetChar(size_t index) const{
    if (index >= size){ throw std::out_of_range("Index out of range"); }
    return data[index];
}

void Array::SetChar(size_t index, unsigned char digit){
    if (index >= size){ throw std::out_of_range("Index out of range"); }
    data[index] = digit;
}