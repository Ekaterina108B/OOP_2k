#include "figure.h"
#include "rhombus.h"

//It is null

//-----------------------------------------

Point Rhombus::GetCenter() const {
    Point center;
    center.x = (vertexes[0].x + vertexes[2].x) / 2.0;
    center.y = (vertexes[0].y + vertexes[2].y) / 2.0;
    return center;
}

double Rhombus::GetArea() const {
    double diagonal_1 = std::sqrt(std::pow(vertexes[2].x - vertexes[0].x, 2) + std::pow(vertexes[2].y - vertexes[0].y, 2));
    double diagonal_2 = std::sqrt(std::pow(vertexes[3].x - vertexes[1].x, 2) + std::pow(vertexes[3].y - vertexes[1].y, 2));
    return (diagonal_1 * diagonal_2) / 2.0;
}

void Rhombus::Reset() {
    Point nul;
    nul.x = 0;
    nul.y = 0;
    for (int i=0; i<4; ++i){ vertexes[i] = nul; }
}

//-----------------------------------------

Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this != &other) {
        std::copy(other.vertexes, other.vertexes+4, vertexes);
    }
    return *this;
}

Rhombus& Rhombus::operator=(Rhombus&& other) noexcept {
    if (this != &other) {
        std::move(other.vertexes, other.vertexes+4, vertexes);
        other.Reset();
    }
    return *this;
}

Figure& Rhombus::operator=(const Figure& other) {
    if (const Rhombus* r = dynamic_cast<const Rhombus*>(&other)) {
        *this = *r;
    }
    return *this;
}

Figure& Rhombus::operator=(Figure&& other) noexcept {
    if (Rhombus* r = dynamic_cast<Rhombus*>(&other)) {
        *this = std::move(*r);
    }
    return *this;
}


bool Rhombus::operator==(const Figure& other) const {
    if (const Rhombus* r = dynamic_cast<const Rhombus*>(&other)) {
        double side_1 = std::pow(vertexes[1].x - vertexes[0].x, 2) + std::pow(vertexes[1].y - vertexes[0].y, 2);
        double side_2 = std::pow(r->vertexes[1].x - r->vertexes[0].x, 2) + std::pow(r->vertexes[1].y - r->vertexes[0].y, 2);
        double diagonal_1v = std::pow(vertexes[2].x - vertexes[0].x, 2) + std::pow(vertexes[2].y - vertexes[0].y, 2);
        double diagonal_2v = std::pow(r->vertexes[2].x - r->vertexes[0].x, 2) + std::pow(r->vertexes[2].y - r->vertexes[0].y, 2);
        double diagonal_1h = std::pow(vertexes[3].x - vertexes[1].x, 2) + std::pow(vertexes[3].y - vertexes[1].y, 2);
        double diagonal_2h = std::pow(r->vertexes[3].x - r->vertexes[1].x, 2) + std::pow(r->vertexes[3].y - r->vertexes[1].y, 2);

        if (!(((diagonal_1v == diagonal_2v) && (diagonal_1h == diagonal_2h)) || ((diagonal_1v == diagonal_2h) && (diagonal_1h == diagonal_2v)))) { return false; }
        if (side_1 != side_2) { return false; }
        return true;
    }
    return false;
}

std::istream& operator>>(std::istream& is, Rhombus& r) {
    for (int i=0; i<4; ++i) {
        is >> r.vertexes[i].x >> r.vertexes[i].y;
    }
    if (!r.Verification()) { throw std::invalid_argument("Invalid Rhombus coordinates"); }
    return is;
}

//-----------------------------------------

void Rhombus::Print(std::ostream& os) const {
    os << "Coordinates of the vertices of the Rhombus:\n";
    for (int i=0; i<4; ++i) {
        os << "(" << vertexes[i].x << ", " << vertexes[i].y << ")" << std::endl;
    }
    os << "\n";
}

bool Rhombus::Verification(void) noexcept {
    double side_1 = std::pow(vertexes[1].x - vertexes[0].x, 2) + std::pow(vertexes[1].y - vertexes[0].y, 2);
    double side_2 = std::pow(vertexes[2].x - vertexes[1].x, 2) + std::pow(vertexes[2].y - vertexes[1].y, 2);
    double side_3 = std::pow(vertexes[3].x - vertexes[2].x, 2) + std::pow(vertexes[3].y - vertexes[2].y, 2);
    double side_4 = std::pow(vertexes[3].x - vertexes[0].x, 2) + std::pow(vertexes[3].y - vertexes[0].y, 2);
    return (side_1 == side_2) && (side_2 == side_3) && (side_3 == side_4);
}