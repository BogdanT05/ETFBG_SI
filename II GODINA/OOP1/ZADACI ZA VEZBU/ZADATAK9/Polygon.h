#ifndef ZADACI_ZA_VEZBU_POLYGON_H
#define ZADACI_ZA_VEZBU_POLYGON_H
#include "Polyline.h"


class Polygon : public Polyline{
public:
    Polygon(const Point* points, int size) : Polyline(points, size){}

    double length() const override;
    Polygon* copy() const override;

protected:
    void write(std::ostream &os) const override;
};


#endif //ZADACI_ZA_VEZBU_POLYGON_H