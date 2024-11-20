#pragma once
#include "figure.h"

template <Scalar T>
class Rhombus : public Figure<T> {
public:
    virtual ~Rhombus() = default;
    
    std::unique_ptr<Figure<T>> Clone() const override {
        auto rhomb = std::make_unique<Rhombus<T>>();
        for (size_t i=0; i<this->vertexes.Size(); ++i){
            rhomb->vertexes.Get(i) = std::make_unique<Point<T>>(this->vertexes.Get(i)->GetX(), this->vertexes.Get(i)->GetY());
        }
        return rhomb;
    }

    //----------------------

    bool IsEqual(const Figure<T>& other) const override  {
        if (const Rhombus<T>* r = dynamic_cast<const Rhombus<T>*>(&other)) {
        double side_1 = std::pow(this->vertexes.Get(1)->GetX() - this->vertexes.Get(0)->GetX(), 2) + std::pow(this->vertexes.Get(1)->GetY() - this->vertexes.Get(0)->GetY(), 2);
        double side_2 = std::pow(r->vertexes.Get(1)->GetX() - r->vertexes.Get(0)->GetX(), 2) + std::pow(r->vertexes.Get(1)->GetY() - r->vertexes.Get(0)->GetY(), 2);
        double diagonal_1v = std::pow(this->vertexes.Get(2)->GetX() - this->vertexes.Get(0)->GetX(), 2) + std::pow(this->vertexes.Get(2)->GetY() - this->vertexes.Get(0)->GetY(), 2);
        double diagonal_2v = std::pow(r->vertexes.Get(2)->GetX() - r->vertexes.Get(0)->GetX(), 2) + std::pow(r->vertexes.Get(2)->GetY() - r->vertexes.Get(0)->GetY(), 2);
        double diagonal_1h = std::pow(this->vertexes.Get(3)->GetX() - this->vertexes.Get(1)->GetX(), 2) + std::pow(this->vertexes.Get(3)->GetY() - this->vertexes.Get(1)->GetY(), 2);
        double diagonal_2h = std::pow(r->vertexes.Get(3)->GetX() - r->vertexes.Get(1)->GetX(), 2) + std::pow(r->vertexes.Get(3)->GetY() - r->vertexes.Get(1)->GetY(), 2);

        if (!(((diagonal_1v == diagonal_2v) && (diagonal_1h == diagonal_2h)) || ((diagonal_1v == diagonal_2h) && (diagonal_1h == diagonal_2v)))) { return false; }
        if (side_1 != side_2) { return false; }
        return true;
    }
    return false;
    }

    friend std::istream& operator>>(std::istream& is, Rhombus<T>& rhomb){
        rhomb.Reset();
        for (size_t i=0; i<4; ++i){
            T x, y;
            is >> x >> y;
            rhomb.vertexes.Add(std::make_unique<Point<T>>(x, y));
        }
        if (!rhomb.Verification()){ throw std::invalid_argument("Invalid Rhombus coordinates"); }
        return is;
    }

    //----------------------

    std::string GetName() const override { return "Rhombus"; }

    bool Verification(void) noexcept {
        double side_1 = std::pow(this->vertexes.Get(1)->GetX() - this->vertexes.Get(0)->GetX(), 2) + std::pow(this->vertexes.Get(1)->GetY() - this->vertexes.Get(0)->GetY(), 2);
        double side_2 = std::pow(this->vertexes.Get(2)->GetX() - this->vertexes.Get(1)->GetX(), 2) + std::pow(this->vertexes.Get(2)->GetY() - this->vertexes.Get(1)->GetY(), 2);
        double side_3 = std::pow(this->vertexes.Get(3)->GetX() - this->vertexes.Get(2)->GetX(), 2) + std::pow(this->vertexes.Get(3)->GetY() - this->vertexes.Get(2)->GetY(), 2);
        double side_4 = std::pow(this->vertexes.Get(3)->GetX() - this->vertexes.Get(0)->GetX(), 2) + std::pow(this->vertexes.Get(3)->GetY() - this->vertexes.Get(0)->GetY(), 2);
        return (side_1 == side_2) && (side_2 == side_3) && (side_3 == side_4);
    }

};