#ifndef ZADACI_ZA_VEZBU_CUBOID_H
#define ZADACI_ZA_VEZBU_CUBOID_H
#include "Object.h"

class Cuboid : public Object{
private:
    double side_a, side_b, side_c;

    void read(std::istream &is) override;
    void write(std::ostream &os) const override;

public:
    Cuboid(double sigma = 1., double side_a = 1., double side_b = 1., double side_c = 1.);
    double volume() const override;
};


#endif //ZADACI_ZA_VEZBU_CUBOID_H