#include "figure.h"
#include "trapezoid.h"

//It is null

//-----------------------------------------

Point Trapezoid::GetCenter() const {
    Point center;
    center.x = 0;
    center.y = 0;
    for (int i=0; i<4; ++i){
        center.x += vertexes[i].x;
        center.y += vertexes[i].y;
    }
    center.x /= 4.0;
    center.y /= 4.0;
    return center;
}

double Trapezoid::GetArea() const {
    return std::fabs(
        vertexes[0].x*vertexes[1].y + vertexes[1].x*vertexes[2].y + vertexes[2].x*vertexes[3].y + vertexes[3].x*vertexes[0].y - (
            vertexes[0].y*vertexes[1].x + vertexes[1].y*vertexes[2].x + vertexes[2].y*vertexes[3].x + vertexes[3].y*vertexes[0].x
        )
    ) / 2.0;
}

void Trapezoid::Reset() {
    Point nul;
    nul.x = 0;
    nul.y = 0;
    for (int i=0; i<4; ++i){ vertexes[i] = nul; }
}

//-----------------------------------------

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other) {
        std::copy(other.vertexes, other.vertexes+4, vertexes);
    }
    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) {
        std::move(other.vertexes, other.vertexes+4, vertexes);
        other.Reset();
    }
    return *this;
}

Figure& Trapezoid::operator=(const Figure& other) {
    if (const Trapezoid* t = dynamic_cast<const Trapezoid*>(&other)) {
        *this = *t;
    }
    return *this;
}

Figure& Trapezoid::operator=(Figure&& other) noexcept {
    if (Trapezoid* t = dynamic_cast<Trapezoid*>(&other)) {
        *this = std::move(*t);
    }
    return *this;
}

bool Trapezoid::operator==(const Figure& other) const {
    if (const Trapezoid* r = dynamic_cast<const Trapezoid*>(&other)) {
        double side_11 = std::pow(vertexes[1].x - vertexes[0].x, 2) + std::pow(vertexes[1].y - vertexes[0].y, 2);
        double side_21 = std::pow(r->vertexes[1].x - r->vertexes[0].x, 2) + std::pow(r->vertexes[1].y - r->vertexes[0].y, 2);
        double side_12 = std::pow(vertexes[2].x - vertexes[1].x, 2) + std::pow(vertexes[2].y - vertexes[1].y, 2);
        double side_22 = std::pow(r->vertexes[2].x - r->vertexes[1].x, 2) + std::pow(r->vertexes[2].y - r->vertexes[1].y, 2);
        double side_13 = std::pow(vertexes[3].x - vertexes[2].x, 2) + std::pow(vertexes[3].y - vertexes[2].y, 2);
        double side_23 = std::pow(r->vertexes[3].x - r->vertexes[2].x, 2) + std::pow(r->vertexes[3].y - r->vertexes[2].y, 2);
        double side_14 = std::pow(vertexes[3].x - vertexes[0].x, 2) + std::pow(vertexes[3].y - vertexes[0].y, 2);
        double side_24 = std::pow(r->vertexes[3].x - r->vertexes[0].x, 2) + std::pow(r->vertexes[3].y - r->vertexes[0].y, 2);

        if (side_11 + side_12 + side_13 + side_14 !=  + side_21 + side_22 + side_23 + side_24) { return false; }
        if (this->GetArea() != other.GetArea()) { return false; }
        return true;
    }
    return false;
}

std::istream& operator>>(std::istream& is, Trapezoid& t) {
    for (int i=0; i<4; ++i) {
        is >> t.vertexes[i].x >> t.vertexes[i].y;
    }
    if (!t.Verification()) { throw std::invalid_argument("Invalid Trapezoid coordinates"); }
    return is;
}

//-----------------------------------------

void Trapezoid::Print(std::ostream& os) const {
    os << "Coordinates of the vertices of the Trapezoid:\n";
    for (int i=0; i<4; ++i) {
        os << "(" << vertexes[i].x << ", " << vertexes[i].y << ")\n";
    }
    os << "\n";
}

bool Trapezoid::Verification(void) noexcept {
    double k[4];
    for (int i=0; i<4; ++i){
        if (vertexes[i].x == vertexes[(i+1)%4].x){
            k[i] = std::numeric_limits<double>::infinity();
        } else {
            k[i] = (vertexes[(i+1)%4].y - vertexes[i].y) / (vertexes[(i+1)%4].x - vertexes[i].x);
        }
    }

    if ((std::fabs(k[0] - k[2]) < 1e-9) || (std::fabs(k[1] - k[3]) < 1e-9)) { return true; }
    return false;
}