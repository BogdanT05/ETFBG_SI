#ifndef ZADACI_ZA_VEZBU_SEGMENT_H
#define ZADACI_ZA_VEZBU_SEGMENT_H
#include "Line.h"
#include "Point.h"


class Segment : public Line{
protected:
    Point start;
    Point end;

    void write(std::ostream &os) const override;
    Segment* copy() const override;

public:
    Segment(const Point &start = Point(-1, -1), const Point &end = Point(1, 1));
    double length() const override;

};


#endif //ZADACI_ZA_VEZBU_SEGMENT_H