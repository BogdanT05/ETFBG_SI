#include "Line.h"
int Line::id_counter = 1;

void Line::write(std::ostream &os) const {
    os << id;
}

std::ostream& operator<<(std::ostream &os, const Line &line) {
    line.write(os);
    return os;
}
