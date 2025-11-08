#include "cuboid.h"

double Cuboid::max_volume = 0;
double Cuboid::total_volume = 0;

// Treba biti u dinamickoj memoriji tako da pravimo pokazivac na novi
// objekat ako je zapremina zadovoljavajuca
Cuboid* Cuboid::make_cuboid(double a, double b, double c) {
    double volume = a * b * c;
    if (total_volume + volume > max_volume) return nullptr;
    total_volume += volume;
    return new Cuboid(a, b, c);
}

Cuboid* Cuboid::read_cuboid() {
    double a,b,c;
    cout << "Unesi stranice: ";
    cin >> a >> b >> c;
    return make_cuboid(a, b, c);
}

void Cuboid::write_cuboid() const {
    cout << "Kvadar sa stranicama : " << this->side_a << " " << this->side_b << " " << this->side_c << endl;
}
