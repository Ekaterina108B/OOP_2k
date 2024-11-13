#pragma once
#include "figure.h"
#include <cmath>

class Rectangle : public Figure {
private:
    Point vertexes[4];

public:
    Rectangle() = default;
    
    Point GetCenter() const override;
    double GetArea() const override;
    void Reset() override;
    
    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;
    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) noexcept override;
    bool operator==(const Figure& other) const override;
    friend std::istream& operator>>(std::istream& is, Rectangle& r);
    
    void Print(std::ostream& os) const override;
    bool Verification();
};