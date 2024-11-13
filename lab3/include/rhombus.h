#pragma once
#include "figure.h"
#include <cmath>

class Rhombus : public Figure {
private:
    Point vertexes[4];

public:
    Rhombus() = default;
    
    Point GetCenter() const override;
    double GetArea() const override;
    void Reset() override;
    
    Rhombus& operator=(const Rhombus& other);
    Rhombus& operator=(Rhombus&& other) noexcept;
    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) noexcept override;
    bool operator==(const Figure& other) const override;
    friend std::istream& operator>>(std::istream& is, Rhombus& r);
    
    void Print(std::ostream& os) const override;
    bool Verification();
};