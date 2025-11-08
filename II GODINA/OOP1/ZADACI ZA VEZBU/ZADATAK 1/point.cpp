#include "point.h"

double Point::distance(const Point& point) const{
    return sqrt(pow(this->x - point.x, 2) + pow(this->y -  point.y, 2));
}

Point Point::read_point() {
    double x_cor, y_cor;
    cout << "Unesite koordinate: ";
    cin >> x_cor >> y_cor;
    return Point(x_cor, y_cor);
}

void Point::write_point() const {
    cout << "(" << this->x << "," << this->y << ")" << endl;
}