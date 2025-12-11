#include "Sphere.h"
#include <cmath>

Sphere::Sphere(double sigma, double r) : Object(sigma){
    radius = r;
}

double Sphere::volume() const {
    return 4./3 * radius * radius * radius * M_PI;
}

void Sphere::read(std::istream &is) {
    Object::read(is);
    std::cout << "Enter radius: ";
    is >> radius;
}

void Sphere::write(std::ostream &os) const {
    os << "Sphere: [";
    Object::write(os);
    os << ", " << radius << "]";
    std::cout << std::endl;
}

