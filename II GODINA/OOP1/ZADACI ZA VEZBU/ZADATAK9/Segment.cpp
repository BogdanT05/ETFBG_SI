#include "Segment.h"
#include <cmath>

void Segment::write(std::ostream &os) const {
    Line::write(os);
    os << " Segment: ";
    os << start << end;
}

Segment *Segment::copy() const {
    return new Segment(*this);
}

Segment::Segment(const Point &start, const Point &end) {
    this->start = start;
    this->end = end;
}

double Segment::length() const {
    return sqrt(
        pow(start.get_x() - end.get_x(), 2) +
        pow(start.get_y() - end.get_y(), 2)
        );
}
