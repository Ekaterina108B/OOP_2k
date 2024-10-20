#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <string>

class Array {
private:
    unsigned char* data;
    size_t size;

public:
    Array();
    Array(const size_t & n, unsigned char t = 0);
    Array(const std::initializer_list< unsigned char> &t);
    Array(const std::string &t);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    virtual ~Array() noexcept;

    size_t GetSize(void);
    unsigned char GetChar(size_t index);
    void SetChar(size_t index, unsigned char digit);
};

#endif