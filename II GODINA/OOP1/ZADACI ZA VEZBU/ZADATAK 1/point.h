
#ifndef ETFBG_SI_POINT_H
#define ETFBG_SI_POINT_H
#include <iostream>
#include <cmath>
using namespace std;

class Point{
private:
    double x, y;
public:
    Point(const double x, const double y){
        this->x = x;
        this->y = y;
    }

    void set_coordinates(const double x_new, const double y_new) {
        this->x = x_new;
        this->y = y_new;
    }

    double get_x() const{return x;}
    double get_y() const{return y;}

    double distance(const Point& point) const;

    static Point read_point();

    void write_point() const;
};


#endif //ETFBG_SI_POINT_H