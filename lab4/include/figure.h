#pragma once
#include <memory>
#include "point.h"

template <Scalar T>
class Figure {
public:
    virtual ~Figure() = default;
    
    virtual Point<T> GetCenter() const = 0;
    virtual double GetArea() const = 0;
    virtual void Reset() = 0;
    virtual std::unique_ptr<Figure<T>> Clone() const = 0;
    virtual std::string GetName() const = 0;
    
    virtual bool operator==(const Figure& other) const = 0;
    virtual Figure& operator=(const Figure& other) = 0;
    virtual Figure& operator=(Figure&& other) noexcept = 0;
    friend std::ostream& operator<<(std::ostream& os, const Figure& fig) {
        fig.Print(os);
        return os;
    };
    friend std::istream& operator>>(std::istream& is, Figure& fig);

    virtual void Print(std::ostream& os) const = 0;
    operator double() const { return GetArea(); }
};