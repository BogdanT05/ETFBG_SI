#include "point.h"

/* Klaca tacka u ravni
 * Postavljanje i dohvatanje koordinata, izracunavanje rastojanja
 * od date tacke, citanje i pisanje tacke.
 */

int main() {
    Point point1(6.23, 1.64);
    Point point2 = Point::read_point();

    point1.write_point();
    point2.write_point();

    cout << "Udaljenost izmedju tacke 1 i tacke 2 je: " << point1.distance(point2) << endl;

    return 0;
}