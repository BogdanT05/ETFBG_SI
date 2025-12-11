#ifndef ZADACI_ZA_VEZBU_SPHERE_H
#define ZADACI_ZA_VEZBU_SPHERE_H
#include "Object.h"

class Sphere : public Object{
private:
    double radius;

    void read(std::istream &is) override;
    void write(std::ostream &os) const override;

public:
    Sphere(double sigma = 1., double r = 1.);
    double volume() const override;
};


#endif //ZADACI_ZA_VEZBU_SPHERE_H