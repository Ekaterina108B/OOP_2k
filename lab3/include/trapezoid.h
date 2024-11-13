#pragma once
#include "figure.h"
#include <cmath>

class Trapezoid : public Figure {
private:
    Point vertexes[4];

public:
    Trapezoid() = default;
    virtual ~Trapezoid() = default;
    
    Point GetCenter() const override;
    double GetArea() const override;
    void Reset() override;
    
    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;
    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) noexcept override;
    bool operator==(const Figure& other) const override;
    friend std::istream& operator>>(std::istream& is, Trapezoid& t);
    
    void Print(std::ostream& os) const override;
    bool Verification(void) noexcept;
};