#pragma once
#include "figure.h"

template <typename T>
class Rhombus : public Figure<T> {
private:
    std::unique_ptr<Point<T>> vertexes[4];

public:
    Rhombus() override{
        for (int i=0; i<4; ++i) {
            vertexes[i] = std::make_unique<Point<T>>();
        }
    };
    virtual ~Rhombus() = default;

    //----------------------

    Point<T> GetCenter() const override {
        T center_x = (vertexes[0]->x + vertexes[2]->x) / 2.0;
        T center_y = (vertexes[0]->y + vertexes[2]->y) / 2.0;
        return Point<T>(center_x, center_y);
    }
    double GetArea() const override{
        double diagonal_1 = std::sqrt(std::pow(vertexes[2]->x - vertexes[0]->x, 2) + std::pow(vertexes[2]->y - vertexes[0]->y, 2));
        double diagonal_2 = std::sqrt(std::pow(vertexes[3]->x - vertexes[1]->x, 2) + std::pow(vertexes[3]->y - vertexes[1]->y, 2));
        return (diagonal_1 * diagonal_2) / 2.0;
    }
    void Reset() override{
        for (int i=0; i<4; ++i){ vertexes[i] = std::make_unique<Point<T>>(0, 0); }
    }
    std::unique_ptr<Figure<T>> Clone() const override {
        auto rect = std::make_unique<Rhombus<T>>();
        for (int i=0; i<4; ++i){
            rect.vertexes[i] = std::make_unique<Point<T>>(other.vertexes[i]->x, other.vertexes[i]->y);
        }
        return rect;
    }
    virtual std::string GetName() const override { return "Rhombus"; }
    
    //----------------------

    Rhombus& operator=(const Rhombus& other){
        if (this != &other) {
            for (int i=0; i<4; ++i){
                vertexes[i] = std::make_unique<Point<T>>(other.vertexes[i]->x, other.vertexes[i]->y); }
        }
        return *this;
    }
    Rhombus& operator=(Rhombus&& other) noexcept{
        if (this != &other) {
            for (int i=0; i<4; ++i){ vertexes[i] = std::move(other.vertexes[i];) }
            other.Reset();
        }
        return *this;
    }
    bool operator==(const Figure& other) const override{
        const Rhombus<T>& r = statuc_cast<const Rhombus<T>&>(other);
        double side_1 = std::pow(vertexes[1]->x - vertexes[0]->x, 2) + std::pow(vertexes[1]->y - vertexes[0]->y, 2);
        double side_2 = std::pow(r->vertexes[1]->x - r->vertexes[0]->x, 2) + std::pow(r->vertexes[1]->y - r->vertexes[0]->y, 2);
        double diagonal_1v = std::pow(vertexes[2]->x - vertexes[0]->x, 2) + std::pow(vertexes[2]->y - vertexes[0]->y, 2);
        double diagonal_2v = std::pow(r->vertexes[2]->x - r->vertexes[0]->x, 2) + std::pow(r->vertexes[2]->y - r->vertexes[0]->y, 2);
        double diagonal_1h = std::pow(vertexes[3]->x - vertexes[1]->x, 2) + std::pow(vertexes[3]->y - vertexes[1]->y, 2);
        double diagonal_2h = std::pow(r->vertexes[3]->x - r->vertexes[1]->x, 2) + std::pow(r->vertexes[3]->y - r->vertexes[1]->y, 2);

        if (!(((diagonal_1v == diagonal_2v) && (diagonal_1h == diagonal_2h)) || ((diagonal_1v == diagonal_2h) && (diagonal_1h == diagonal_2v)))) { return false; }
        if (side_1 != side_2) { return false; }
        return true;
    }
    friend std::istream& operator>>(std::istream& is, Rectangl<T>& r){
        for (int i=0; i<4; ++i){
            T x, y;
            is >> x >> y;
            r.vertexes[i] = std::make_unique<Point<T>>(x, y);
        }
        return is;
    }

    //----------------------

    void Print(std::ostream& os) const {
        os << "Coordinates of the vertices of the Rhombus:" << std::endl;
        for (int i=0; i<4; ++i) {
            os << "(" << vertexes[i]->x << ", " << vertexes[i]->y << ")" << std::endl;
        }
        os << "\n";
    }

    bool Verification(void) noexcept {
        double side_1 = std::pow(vertexes[1]->x - vertexes[0]->x, 2) + std::pow(vertexes[1]->y - vertexes[0]->y, 2);
        double side_2 = std::pow(vertexes[2]->x - vertexes[1]->x, 2) + std::pow(vertexes[2]->y - vertexes[1]->y, 2);
        double side_3 = std::pow(vertexes[3]->x - vertexes[2]->x, 2) + std::pow(vertexes[3]->y - vertexes[2]->y, 2);
        double side_4 = std::pow(vertexes[3]->x - vertexes[0]->x, 2) + std::pow(vertexes[3]->y - vertexes[0]->y, 2);
        return (side_1 == side_2) && (side_2 == side_3) && (side_3 == side_4);
    }
};