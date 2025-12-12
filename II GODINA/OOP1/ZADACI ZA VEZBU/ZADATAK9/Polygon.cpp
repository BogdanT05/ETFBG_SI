#include "Polygon.h"

#include "Segment.h"

double Polygon::length() const {
    return Polyline::length() + Segment(points[0], points[size-1]).length();
}

Polygon * Polygon::copy() const {
    return new Polygon(*this);
}

void Polygon::write(std::ostream &os) const {
    Line::write(os);
    os << "Polygon: ";
    Point::write_array(os, points, size);
}
