#include "Complex.h"
#include <cmath>

namespace complex {
    std::ostream& operator << (std::ostream &os, const Complex &complex) {
    return os << "(" << complex.real << (complex.imaginary >= 0? "+" : "") << complex.imaginary << "i)";
}

std::istream& operator >> (std::istream &is, Complex &complex) {
    std::cout << "Provide real and imaginary parts: ";
    return is >> complex.real >> complex.imaginary;
}

Complex operator + (const Complex &complex1, const Complex &complex2) {
    return {complex1.real + complex2.real, complex1.imaginary + complex2.imaginary};
}

Complex operator-(const Complex &complex1, const Complex &complex2) {
    return {complex1.real - complex2.real, complex1.imaginary - complex2.imaginary};
}

Complex &Complex::operator+=(const Complex &complex) {
    return *this = *this + complex;
}

Complex & Complex::operator-=(const Complex &complex) {
    return *this = *this - complex;
}

Complex Complex::operator * (const Complex &complex) const {
    // (a+bi) * (c+di) = (ac-bd) + (ad+bc)i
    return {
        this->real*complex.real - this->imaginary*complex.imaginary,
        this->real*complex.imaginary + this->imaginary*complex.real
    };
}

double real(const Complex &complex) {
    return complex.real;
}

double imaginary(const Complex &complex) {
    return complex.imaginary;
}

double abs(const Complex &complex) {
    return std::sqrt(complex.real * complex.real + complex.imaginary * complex.imaginary);
}

double arg(const Complex &complex) {
    return std::atan2(complex.imaginary, complex.real) * 180 / M_PI;
}

Complex Complex::operator + () const {
    return *this;
}

Complex Complex::operator ~ () const {
    return {real, -imaginary};
}

bool operator == (const Complex &complex1, const Complex &complex2) {
    return std::abs(complex1.real - complex2.real) < Complex::delta &&
        std::abs(complex1.imaginary - complex2.imaginary) < Complex::delta;
}

bool operator != (const Complex &complex1, const Complex &complex2) {
    return !(complex1 == complex2);
}

Complex operator ""_i(unsigned long long const value) {
    return {0,  static_cast<double>(value)};
}
Complex operator ""_i(long double const value) {
    return {0,  static_cast<double>(value)};
}
}


