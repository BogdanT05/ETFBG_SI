//
// Created by bgdnt on 11/7/2025.
//

#ifndef ZADATAK1_ANGLE_H
#define ZADATAK1_ANGLE_H
#define FAKTOR (3.14/180)
#include <iostream>
using namespace std;

class Angle {
private:
    double radians;
public:
    explicit Angle(double rad=0) {
        this->radians = rad;
    }

    Angle(int degrees, int minutes, int seconds) {
        this->radians = (degrees + minutes/60.0 + seconds/3600.0)*FAKTOR;
    }

    double get_radians() const{return this->radians;}
    int get_degrees() const{return int(this->radians / FAKTOR);}
    int get_minutes() const{return int(this->radians / FAKTOR * 60) % 60;}
    int get_seconds() const{return int(this->radians / FAKTOR * 3600) % 60;}

    void get_deg_min_sec(int &degree, int &minute, int &second) {
        degree = get_degrees();
        minute = get_minutes();
        second = get_seconds();
    }

    // Vracamo referencu zato sto hocemo da promenimo vec postojeci objekat bez kopiranja
    // Ako bi pass by value ne bi menjali trenutni objekat vec bi napravili kopiju

    Angle& add_angles(Angle &angle) {
        this->radians = this->radians + angle.radians;
        return *this;
    }

    Angle& multiply_angle(int number) {
        this->radians = this->radians * number;
        return *this;
    }

    // Staticka metoda zato sto nam omogucava pravljenje novog objekta.
    static Angle read_angle();

    void write_angle() const;
};


#endif //ZADATAK1_ANGLE_H