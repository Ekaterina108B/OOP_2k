#include "rectangle.h"

//It is null

//-----------------------------------------

Point Rectangle::GetCenter() const {
    Point center;
    center.x = (vertexes[0].x + vertexes[2].x) / 2.0;
    center.y = (vertexes[0].y + vertexes[2].y) / 2.0;
    return center;
}

double Rectangle::GetArea() const {
    double width = std::sqrt(std::pow(vertexes[3].x - vertexes[0].x, 2) + std::pow(vertexes[3].y - vertexes[0].y, 2));
    double height = std::sqrt(std::pow(vertexes[1].x - vertexes[0].x, 2) + std::pow(vertexes[1].y - vertexes[0].y, 2));
    return width * height;
}

void Rectangle::Reset() {
    Point nul;
    nul.x = 0;
    nul.y = 0;
    for (int i=0; i<4; ++i){ vertexes[i] = nul; }
}

//-----------------------------------------

Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) {
        std::copy(other.vertexes, other.vertexes+4, vertexes);
    }
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this != &other) {
        std::move(other.vertexes, other.vertexes+4, vertexes);
        other.Reset();
    }
    return *this;
}

Figure& Rectangle::operator=(const Figure& other) {
    if (const Rectangle* r = dynamic_cast<const Rectangle*>(&other)) {
        *this = *r;
    }
    return *this;
}

Figure& Rectangle::operator=(Figure&& other) noexcept {
    if (Rectangle* r = dynamic_cast<Rectangle*>(&other)) {
        *this = std::move(*r);
    }
    return *this;
}


bool Rectangle::operator==(const Figure& other) const {
    if (const Rectangle* r = dynamic_cast<const Rectangle*>(&other)) {
        double width_1 = std::pow(vertexes[3].x - vertexes[0].x, 2) + std::pow(vertexes[3].y - vertexes[0].y, 2);
        double width_2 = std::pow(r->vertexes[3].x - r->vertexes[0].x, 2) + std::pow(r->vertexes[3].y - r->vertexes[0].y, 2);
        double height_1 = std::pow(vertexes[1].x - vertexes[0].x, 2) + std::pow(vertexes[1].y - vertexes[0].y, 2);
        double height_2 = std::pow(r->vertexes[1].x - r->vertexes[0].x, 2) + std::pow(r->vertexes[1].y - r->vertexes[0].y, 2);
        double diagonal_1 = std::pow(vertexes[2].x - vertexes[0].x, 2) + std::pow(vertexes[2].y - vertexes[0].y, 2);
        double diagonal_2 = std::pow(r->vertexes[2].x - r->vertexes[0].x, 2) + std::pow(r->vertexes[2].y - r->vertexes[0].y, 2);

        if (!(((width_1 == width_2) && (height_1 == height_2)) || ((width_1 == height_2) && (height_1 == width_2)))) { return false; }
        if (diagonal_1 != diagonal_2) { return false; }
        return true;
    }
    return false;
}

std::istream& operator>>(std::istream& is, Rectangle& r) {
    for (int i=0; i<4; ++i) {
        is >> r.vertexes[i].x >> r.vertexes[i].y;
    }
    if (!r.Verification()) { throw std::invalid_argument("Invalid rectangle coordinates"); }
    return is;
}

//-----------------------------------------

void Rectangle::Print(std::ostream& os) const {
    os << "Coordinates of the vertices of the rectangle:" << std::endl;
    for (int i=0; i<4; ++i) {
        os << "(" << vertexes[i].x << ", " << vertexes[i].y << ")" << std::endl;
    }
    os << "\n";
}

bool Rectangle::Verification() noexcept {
    double width_1 = std::pow(vertexes[3].x - vertexes[0].x, 2) + std::pow(vertexes[3].y - vertexes[0].y, 2);
    double width_2 = std::pow(vertexes[2].x - vertexes[1].x, 2) + std::pow(vertexes[2].y - vertexes[1].y, 2);
    double height_1 = std::pow(vertexes[1].x - vertexes[0].x, 2) + std::pow(vertexes[1].y - vertexes[0].y, 2);
    double height_2 = std::pow(vertexes[2].x - vertexes[3].x, 2) + std::pow(vertexes[2].y - vertexes[3].y, 2);
    double diagonal_1 = std::pow(vertexes[2].x - vertexes[0].x, 2) + std::pow(vertexes[2].y - vertexes[0].y, 2);
    double diagonal_2 = std::pow(vertexes[1].x - vertexes[3].x, 2) + std::pow(vertexes[1].y - vertexes[3].y, 2);
    return (width_1 == width_2) && (height_1 == height_2) && (diagonal_1 == diagonal_2);
}