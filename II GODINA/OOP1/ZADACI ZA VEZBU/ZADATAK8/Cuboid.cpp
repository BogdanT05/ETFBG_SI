#include "Cuboid.h"

Cuboid::Cuboid(double sigma, double side_a, double side_b, double side_c) : Object(sigma){
    this->side_a = side_a;
    this->side_b = side_b;
    this->side_c = side_c;
}

void Cuboid::read(std::istream &is) {
    Object::read(is);
    std::cout << "Enter sides: ";
    is >> side_a >> side_b >> side_c;
}

void Cuboid::write(std::ostream &os) const {
    os << "Cuboid [";
    Object::write(os);
    os << ", " << side_a << ", " << side_b << ", " << side_c << "]";
    os << std::endl;
}

double Cuboid::volume() const {
    return side_a * side_b * side_c;
}
