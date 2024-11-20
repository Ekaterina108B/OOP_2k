#pragma once
#include <memory>
#include <string>
#include <cmath>
#include "point.h"
#include "array.h"

template <Scalar T>
class Figure {
protected:
    Array<std::unique_ptr<Point<T>>> vertexes;

    Point<T> CalculationCenter() const {
        if (vertexes.Size() == 0){ throw std::runtime_error("No vertexes in the figure"); }        
        T total_x = 0;
        T total_y = 0;
        for (size_t i=0; i<vertexes.Size(); ++i){
            total_x += vertexes.Get(i)->GetX();
            total_y += vertexes.Get(i)->GetY();
        }
        return Point<T>(total_x/vertexes.Size(), total_y/vertexes.Size());
    }

    double CalculationArea() const noexcept {
        double f_gauss = 0;
        for (size_t i=0; i<vertexes.Size()-1; ++i){
            f_gauss += vertexes.Get(i)->GetX()*vertexes.Get(i+1)->GetY() - vertexes.Get(i+1)->GetX()*vertexes.Get(i)->GetY();
        }
        f_gauss += vertexes.GetEnd()->GetX()*vertexes.Get(0)->GetY() - vertexes.GetEnd()->GetY()*vertexes.Get(0)->GetX();
        return std::fabs(f_gauss) / 2.0;
    }

public:
    Figure() = default;

    Figure(const Figure& other) {
        for (size_t i=0; i<other.vertexes.Size(); ++i){
            vertexes.Add(std::make_unique<Point<T>>(other.vertexes.Get(i)->GetX(), other.vertexes.Get(i)->GetY()));
        }
    }

    virtual ~Figure() = default;
    
    void Reset(){
        vertexes.Reset();
    }

    virtual std::unique_ptr<Figure<T>> Clone() const = 0;

    //----------------------

    Figure& operator=(const Figure& other){
        if (!(this == &other)){
            for (size_t i=0; i<other.vertexes.Size(); ++i){
                vertexes.Add(std::make_unique<Point<T>>(other.vertexes.Get(i)->GetX(), other.vertexes.Get(i)->GetY()));
            }
        }
        return *this;
    }

    Figure& operator=(Figure&& other) noexcept {
        if (!(this == &other)){
            vertexes = std::move(other.vertexes);
        }
        return *this;
    }

    bool operator==(const Figure<T>& other) const { return IsEqual(other); }

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        for (size_t i=0; i<fig.vertexes.Size(); ++i){
            os << *fig.vertexes.Get(i) << " ";
        }
        return os;
    };

    //----------------------

    Point<T> GetCenter() const { return CalculationCenter(); }
    double GetArea() const { return CalculationArea(); }
    virtual std::string GetName() const = 0;
    virtual operator double() const { return GetArea(); }
    virtual bool IsEqual(const Figure<T>& other) const {
        if (vertexes.Size() != other.vertexes.Size()) { return false; }
        for (size_t i=0; i<vertexes.Size(); ++i) {
            if (vertexes.Get(i)->GetX() != other.vertexes.Get(i)->GetX() ||
                vertexes.Get(i)->GetY() != other.vertexes.Get(i)->GetY()) {
                return false;
            }
        }
        return true;
    }
    
};