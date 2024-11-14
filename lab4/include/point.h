#pragma once
#include <iostream>
#include <concepts>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
class Point {
private:
    T x;
    T y;
    
public:
    Point(T x = 0, T y = 0) : x(x), y(y) {}
    virtual ~Point() = default;

    T GetX() const noexcept { return x; }
    T GetY() const noexcept { return y; }

    void SetX(T x) { this->x = x; }
    void SetY(T y) { this->y = y; }
};