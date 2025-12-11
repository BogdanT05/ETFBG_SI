#ifndef ZADACI_ZA_VEZBU_OBJECT_H
#define ZADACI_ZA_VEZBU_OBJECT_H
#include <iostream>

class Object {
protected:
    double sigma;

    virtual void write(std::ostream &os) const {os << this->sigma;}
    virtual void read(std::istream &is) {std::cout << "Enter sigma: "; is >> this->sigma;}

public:
    Object(double sigma = 1.) : sigma(sigma){}

    virtual double volume() const = 0;
    double weight() const {return sigma * volume();}

    double get_sigma() const {return sigma;}
    void set_sigma(double sigma_) {sigma = sigma_;}

    friend std::ostream& operator << (std::ostream &os, const Object &object) {object.write(os); return os;}
    friend std::istream& operator >> (std::istream &is, Object &object) {object.read(is); return is;}

    virtual ~Object() = default;
};


#endif //ZADACI_ZA_VEZBU_OBJECT_H