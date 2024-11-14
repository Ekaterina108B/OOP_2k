#pragma once
#include "figure.h"

template <class T>
class Rectangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>> vertexes[4];

public:
    Rectangle() = default;
    virtual ~Rectangle() = default;
    
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
    bool Verification(void) noexcept;
};