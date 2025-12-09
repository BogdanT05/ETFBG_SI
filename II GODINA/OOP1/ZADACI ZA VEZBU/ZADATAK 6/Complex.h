#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>

namespace complex {
    class Complex {
    private:
        // real + i*imag
        double real, imaginary;
        static constexpr double delta = 0.001;
    public:
        Complex(double real = 0, double imaginary = 0) : real(real), imaginary(imaginary){}

        // Friend funkcija preklapanja operatora za ispis i upis
        friend std::ostream& operator << (std::ostream &os, const Complex &complex);
        friend std::istream& operator >> (std::istream &is, Complex &complex);

        // Getteri
        double get_real() const {return real;}
        double get_imaginary() const {return imaginary;}

        // Setteri
        void set_real(double real_) {this->real = real_;}
        void set_imaginary(double imaginary_) {this->imaginary = imaginary_;}

        friend double real(const Complex &complex);
        friend double imaginary(const Complex &complex);

        // Preklapanje operatora
        friend Complex operator + (const Complex &complex1, const Complex &complex2);
        friend Complex operator - (const Complex &complex1, const Complex &complex2);

        Complex& operator += (const Complex &complex);
        Complex& operator -= (const Complex &complex);

        Complex operator * (const Complex &complex) const;
        friend double abs(const Complex &complex);
        friend double arg(const Complex &complex);

        friend bool operator == (const Complex &complex1, const Complex &complex2);
        friend bool operator != (const Complex &complex1, const Complex &complex2);

        Complex operator + () const;
        Complex operator ~ () const;

    };

    // Preklapanje literala
    Complex operator ""_i (unsigned long long const value);
    Complex operator ""_i(long double const value);
}

#endif //PRETRAZIVANJE_U_STABLU_COMPLEX_H