#ifndef ZADACI_ZA_VEZBU_POINT_H
#define ZADACI_ZA_VEZBU_POINT_H
#include <iostream>


class Point {
private:
    double x, y;
public:
    Point(double x = 0, double y = 0) : x(x), y(y){}

    double get_x () const {return x;}
    double get_y () const {return y;}

    friend std::ostream& operator << (std::ostream& os, const Point &point);
    static void write_array(std::ostream& os, const Point *points, int length);
};


#endif //ZADACI_ZA_VEZBU_POINT_H