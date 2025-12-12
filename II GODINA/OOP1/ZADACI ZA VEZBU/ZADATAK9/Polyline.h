#ifndef ZADACI_ZA_VEZBU_POLYLINE_H
#define ZADACI_ZA_VEZBU_POLYLINE_H
#include "Point.h"
#include "Line.h"

class Polyline : public Line{
protected:
    Point *points;
    int size;

    void clear();
    void move(Polyline &polyline);
    void copy(const Point *points_, int length_);
    void write(std::ostream &os) const override;

    Polyline* copy() const override {return new Polyline(*this);}
    friend void swap(Polyline &polyline_1, Polyline &polyline_2) noexcept;
public:
    Polyline(const Point *points, int length);
    Polyline(const Polyline &polyline);
    Polyline(Polyline &&polyline) noexcept;

    // Polyline& operator=(const Polyline &polyline);
    // Polyline& operator=(const Polyline &&polyline);
    Polyline& operator=(Polyline polyline);

    double length() const override;


    ~Polyline() override;
};


#endif //ZADACI_ZA_VEZBU_POLYLINE_H