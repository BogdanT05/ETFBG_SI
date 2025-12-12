#include "Point.h"

inline std::ostream& operator << (std::ostream& os, const Point &point) {
    return os << "(" << point.x << ", " << point.y << ")" << std::endl;
}

void Point::write_array(std::ostream &os, const Point *points, int length) {
    for (int i = 0; i < length; i++) {
        os << points[i];
    }
}

