#pragma once
#include "figure.h"

template <Scalar T>
class Rectangle : public Figure<T> {
public:
    virtual ~Rectangle() = default;
    
    std::unique_ptr<Figure<T>> Clone() const override {
        auto rect = std::make_unique<Rectangle<T>>();
        for (size_t i=0; i<this->vertexes.Size(); ++i){
            rect->vertexes.Get(i) = std::make_unique<Point<T>>(this->vertexes.Get(i)->GetX(), this->vertexes.Get(i)->GetY());
        }
        return rect;
    }

    //----------------------

    bool IsEqual(const Figure<T>& other) const override {
        if (const Rectangle<T>* r = dynamic_cast<const Rectangle<T>*>(&other)) {
        double width_1 = std::pow(this->vertexes.Get(3)->GetX() - this->vertexes.Get(0)->GetX(), 2) + std::pow(this->vertexes.Get(3)->GetY() - this->vertexes.Get(0)->GetY(), 2);
        double width_2 = std::pow(r->vertexes.Get(3)->GetX() - r->vertexes.Get(0)->GetX(), 2) + std::pow(r->vertexes.Get(3)->GetY() - r->vertexes.Get(0)->GetY(), 2);
        double height_1 = std::pow(this->vertexes.Get(1)->GetX() - this->vertexes.Get(0)->GetX(), 2) + std::pow(this->vertexes.Get(1)->GetY() - this->vertexes.Get(0)->GetY(), 2);
        double height_2 = std::pow(r->vertexes.Get(1)->GetX() - r->vertexes.Get(0)->GetX(), 2) + std::pow(r->vertexes.Get(1)->GetY() - r->vertexes.Get(0)->GetY(), 2);
        double diagonal_1 = std::pow(this->vertexes.Get(2)->GetX() - this->vertexes.Get(0)->GetX(), 2) + std::pow(this->vertexes.Get(2)->GetY() - this->vertexes.Get(0)->GetY(), 2);
        double diagonal_2 = std::pow(r->vertexes.Get(2)->GetX() - r->vertexes.Get(0)->GetX(), 2) + std::pow(r->vertexes.Get(2)->GetY() - r->vertexes.Get(0)->GetY(), 2);

        if (!(((width_1 == width_2) && (height_1 == height_2)) || ((width_1 == height_2) && (height_1 == width_2)))) { return false; }
        if (diagonal_1 != diagonal_2) { return false; }
        return true;
    }
    return false;
    }

    friend std::istream& operator>>(std::istream& is, Rectangle<T>& rect){
        rect.Reset();
        for (size_t i=0; i<4; ++i){
            T x, y;
            is >> x >> y;
            rect.vertexes.Add(std::make_unique<Point<T>>(x, y));
        }
        if (!rect.Verification()){ throw std::invalid_argument("Invalid rectangle coordinates"); }
        return is;
    }

    //----------------------

    std::string GetName() const override { return "Rectangle"; }

    bool Verification(void) noexcept {
        double width_1 = std::pow(this->vertexes.Get(3)->GetX() - this->vertexes.Get(0)->GetX(), 2) + std::pow(this->vertexes.Get(3)->GetY() - this->vertexes.Get(0)->GetY(), 2);
        double width_2 = std::pow(this->vertexes.Get(2)->GetX() - this->vertexes.Get(1)->GetX(), 2) + std::pow(this->vertexes.Get(2)->GetY() - this->vertexes.Get(1)->GetY(), 2);
        double height_1 = std::pow(this->vertexes.Get(1)->GetX() - this->vertexes.Get(0)->GetX(), 2) + std::pow(this->vertexes.Get(1)->GetY() - this->vertexes.Get(0)->GetY(), 2);
        double height_2 = std::pow(this->vertexes.Get(2)->GetX() - this->vertexes.Get(3)->GetX(), 2) + std::pow(this->vertexes.Get(2)->GetY() - this->vertexes.Get(3)->GetY(), 2);
        double diagonal_1 = std::pow(this->vertexes.Get(2)->GetX() - this->vertexes.Get(0)->GetX(), 2) + std::pow(this->vertexes.Get(2)->GetY() - this->vertexes.Get(0)->GetY(), 2);
        double diagonal_2 = std::pow(this->vertexes.Get(1)->GetX() - this->vertexes.Get(3)->GetX(), 2) + std::pow(this->vertexes.Get(1)->GetY() - this->vertexes.Get(3)->GetY(), 2);
        return (width_1 == width_2) && (height_1 == height_2) && (diagonal_1 == diagonal_2);
    }

};