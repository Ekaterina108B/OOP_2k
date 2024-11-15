#pragma once
#include "figure.h"

template <Scalar T>
class Trapezoid : public Figure<T> {
public:
    virtual ~Trapezoid() = default;
    
    std::unique_ptr<Figure<T>> Clone() const override {
        auto trapez = std::make_unique<Trapezoid<T>>();
        for (size_t i=0; i<this->vertexes.Size(); ++i){
            trapez->vertexes.Get(i) = std::make_unique<Point<T>>(this->vertexes.Get(i)->GetX(), this->vertexes.Get(i)->GetY());
        }
        return trapez;
    }

    //----------------------

    bool IsEqual(const Figure<T>& other) const override  {
        if (const Trapezoid<T>* r = dynamic_cast<const Trapezoid<T>*>(&other)) {
        double side_11 = std::pow(this->vertexes.Get(1)->GetX() - this->vertexes.Get(0)->GetX(), 2) + std::pow(this->vertexes.Get(1)->GetY() - this->vertexes.Get(0)->GetY(), 2);
        double side_21 = std::pow(r->vertexes.Get(1)->GetX() - r->vertexes.Get(0)->GetX(), 2) + std::pow(r->vertexes.Get(1)->GetY() - r->vertexes.Get(0)->GetY(), 2);
        double side_12 = std::pow(this->vertexes.Get(2)->GetX() - this->vertexes.Get(1)->GetX(), 2) + std::pow(this->vertexes.Get(2)->GetY() - this->vertexes.Get(1)->GetY(), 2);
        double side_22 = std::pow(r->vertexes.Get(2)->GetX() - r->vertexes.Get(1)->GetX(), 2) + std::pow(r->vertexes.Get(2)->GetY() - r->vertexes.Get(1)->GetY(), 2);
        double side_13 = std::pow(this->vertexes.Get(3)->GetX() - this->vertexes.Get(2)->GetX(), 2) + std::pow(this->vertexes.Get(3)->GetY() - this->vertexes.Get(2)->GetY(), 2);
        double side_23 = std::pow(r->vertexes.Get(3)->GetX() - r->vertexes.Get(2)->GetX(), 2) + std::pow(r->vertexes.Get(3)->GetY() - r->vertexes.Get(2)->GetY(), 2);
        double side_14 = std::pow(this->vertexes.Get(3)->GetX() - this->vertexes.Get(0)->GetX(), 2) + std::pow(this->vertexes.Get(3)->GetY() - this->vertexes.Get(0)->GetY(), 2);
        double side_24 = std::pow(r->vertexes.Get(3)->GetX() - r->vertexes.Get(0)->GetX(), 2) + std::pow(r->vertexes.Get(3)->GetY() - r->vertexes.Get(0)->GetY(), 2);

        if (side_11 + side_12 + side_13 + side_14 !=  + side_21 + side_22 + side_23 + side_24) { return false; }
        if (this->GetArea() != other.GetArea()) { return false; }
        return true;
    }
    return false;
    }

    friend std::istream& operator>>(std::istream& is, Trapezoid<T>& trapez){
        trapez.Reset();
        for (size_t i=0; i<4; ++i){
            T x, y;
            is >> x >> y;
            trapez.vertexes.Add(std::make_unique<Point<T>>(x, y));
        }
        if (!trapez.Verification()){ throw std::invalid_argument("Invalid Trapezoid coordinates"); }
        return is;
    }

    //----------------------

    std::string GetName() const override { return "Trapezoid"; }

    bool Verification(void) noexcept {
        double k[4];
        for (int i=0; i<4; ++i){
            if (this->vertexes.Get(i)->GetX() == this->vertexes.Get((i+1)%4)->GetX()){
                k[i] = std::numeric_limits<double>::infinity();
            } else {
                k[i] = (this->vertexes.Get((i+1)%4)->GetY() - this->vertexes.Get(i)->GetY()) / (this->vertexes.Get((i+1)%4)->GetX() - this->vertexes.Get(i)->GetX());
            }
        }
        if ((std::fabs(k[0] - k[2]) < 1e-9) || (std::fabs(k[1] - k[3]) < 1e-9)) { return true; }
        return false;
    }

};