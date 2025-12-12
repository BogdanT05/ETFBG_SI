#include "Polyline.h"

#include "Segment.h"

void swap(Polyline &polyline_1, Polyline &polyline_2) noexcept{
    std::swap(polyline_1.size, polyline_2.size);
    std::swap(polyline_1.points, polyline_2.points);
}

void Polyline::clear() {
    delete [] points;
    points = nullptr;
    size = 0;
}

void Polyline::move(Polyline &polyline) {
    points = polyline.points;
    size = polyline.size;
    polyline.points = nullptr;
}

void Polyline::copy(const Point *points_, int size_) {
    points = new Point[size_];
    size = size_;

    for (int i = 0; i < size_; i++) {
        points[i] = points_[i];
    }
}

void Polyline::write(std::ostream &os) const {
    Line::write(os);
    os << "Polyline: ";
    Point::write_array(os, points, size);
}

double Polyline::length() const {
    double distance = 0.0;
    for (int i = 0; i < size-1; i++) {
        distance += Segment(points[i], points[i+1]).length();
    }

    return distance;
}

Polyline::Polyline(const Point *points, int size_) {
    copy(points, size_);
}

Polyline::Polyline(const Polyline &polyline) {
    copy(polyline.points, polyline.size);
}

Polyline::Polyline(Polyline &&polyline) noexcept {
    move(polyline);
}

Polyline & Polyline::operator=(Polyline polyline) {
    swap(*this, polyline);
    return *this;
}


Polyline::~Polyline() {
    clear();
}
