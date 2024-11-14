#pragma once
#include "figure.h"

template <typename T>
class Rectangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>> vertexes[4];

public:
    Rectangle() override{
        for (int i=0; i<4; ++i) {
            vertexes[i] = std::make_unique<Point<T>>();
        }
    };
    virtual ~Rectangle() = default;

    //----------------------

    Point<T> GetCenter() const override {
        T center_x = (vertexes[0]->x + vertexes[2]->x) / 2.0;
        T center_y = (vertexes[0]->y + vertexes[2]->y) / 2.0;
        return Point<T>(center_x, center_y);
    }
    double GetArea() const override{
        double width = std::sqrt(std::pow(vertexes[3]->x - vertexes[0]->x, 2) + std::pow(vertexes[3]->y - vertexes[0]->y, 2));
        double height = std::sqrt(std::pow(vertexes[1]->x - vertexes[0]->x, 2) + std::pow(vertexes[1]->y - vertexes[0]->y, 2));
        return width * height;
    }
    void Reset() override{
        for (int i=0; i<4; ++i){ vertexes[i] = std::make_unique<Point<T>>(0, 0); }
    }
    std::unique_ptr<Figure<T>> Clone() const override {
        auto rect = std::make_unique<Rectangle<T>>();
        for (int i=0; i<4; ++i){
            rect.vertexes[i] = std::make_unique<Point<T>>(other.vertexes[i]->x, other.vertexes[i]->y);
        }
        return rect;
    }
    virtual std::string GetName() const override { return "Rectangle"; }
    
    //----------------------

    Rectangle& operator=(const Rectangle& other){
        if (this != &other) {
            for (int i=0; i<4; ++i){
                vertexes[i] = std::make_unique<Point<T>>(other.vertexes[i]->x, other.vertexes[i]->y); }
        }
        return *this;
    }
    Rectangle& operator=(Rectangle&& other) noexcept{
        if (this != &other) {
            for (int i=0; i<4; ++i){ vertexes[i] = std::move(other.vertexes[i];) }
            other.Reset();
        }
        return *this;
    }
    bool operator==(const Figure& other) const override{
        const Rectangle<T>& r = statuc_cast<const Rectangle<T>&>(other);
        double width_1 = std::pow(vertexes[3]->x - vertexes[0]->x, 2) + std::pow(vertexes[3]->y - vertexes[0]->y, 2);
        double width_2 = std::pow(r->vertexes[3]->x - r->vertexes[0]->x, 2) + std::pow(r->vertexes[3]->y - r->vertexes[0]->y, 2);
        double height_1 = std::pow(vertexes[1]->x - vertexes[0]->x, 2) + std::pow(vertexes[1]->y - vertexes[0]->y, 2);
        double height_2 = std::pow(r->vertexes[1]->x - r->vertexes[0]->x, 2) + std::pow(r->vertexes[1]->y - r->vertexes[0]->y, 2);
        double diagonal_1 = std::pow(vertexes[2]->x - vertexes[0]->x, 2) + std::pow(vertexes[2]->y - vertexes[0]->y, 2);
        double diagonal_2 = std::pow(r->vertexes[2]->x - r->vertexes[0]->x, 2) + std::pow(r->vertexes[2]->y - r->vertexes[0]->y, 2);

        if (!(((width_1 == width_2) && (height_1 == height_2)) || ((width_1 == height_2) && (height_1 == width_2)))) { return false; }
        if (diagonal_1 != diagonal_2) { return false; }
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
        os << "Coordinates of the vertices of the rectangle:" << std::endl;
        for (int i=0; i<4; ++i) {
            os << "(" << vertexes[i]->x << ", " << vertexes[i]->y << ")" << std::endl;
        }
        os << "\n";
    }

    bool Verification(void) noexcept {
        double width_1 = std::pow(vertexes[3]->x - vertexes[0]->x, 2) + std::pow(vertexes[3]->y - vertexes[0]->y, 2);
        double width_2 = std::pow(vertexes[2]->x - vertexes[1]->x, 2) + std::pow(vertexes[2]->y - vertexes[1]->y, 2);
        double height_1 = std::pow(vertexes[1]->x - vertexes[0]->x, 2) + std::pow(vertexes[1]->y - vertexes[0]->y, 2);
        double height_2 = std::pow(vertexes[2]->x - vertexes[3]->x, 2) + std::pow(vertexes[2]->y - vertexes[3]->y, 2);
        double diagonal_1 = std::pow(vertexes[2]->x - vertexes[0]->x, 2) + std::pow(vertexes[2]->y - vertexes[0]->y, 2);
        double diagonal_2 = std::pow(vertexes[1]->x - vertexes[3]->x, 2) + std::pow(vertexes[1]->y - vertexes[3]->y, 2);
        return (width_1 == width_2) && (height_1 == height_2) && (diagonal_1 == diagonal_2);
    }
};