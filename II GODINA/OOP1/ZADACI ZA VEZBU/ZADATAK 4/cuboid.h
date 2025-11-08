#ifndef ZADACI_ZA_VEZBU_CUBOID_H
#define ZADACI_ZA_VEZBU_CUBOID_H
#include <iostream>
using namespace std;

class Cuboid {
private:
    double side_a, side_b, side_c;
    static double total_volume;
    static double max_volume;

    // Zelimo da omogucimo pravljenje samo ako je zapremina
    // zadovoljenja zato je konstruktor private
    Cuboid(double a, double b, double c) {
        this->side_a = a;
        this->side_b = b;
        this->side_c = c;
    }

public:
    Cuboid (const Cuboid &cuboid) = delete;

    static double get_total_volume() { return total_volume;}
    static double get_max_volume() {return max_volume;}
    static void set_max_volume(double max){max_volume = max;}
    static Cuboid* read_cuboid();
    static Cuboid* make_cuboid(double a, double b, double c);

    double get_side_a() const{return this->side_a;}
    double get_side_b() const{return this->side_b;}
    double get_side_c() const{return this->side_c;}

    double calculate_volume () const{
        return this->side_a * this->side_b * this->side_c;
    }

    void write_cuboid() const;
    ~Cuboid() {
        total_volume = total_volume - this->calculate_volume();
    }
};

#endif //ZADACI_ZA_VEZBU_CUBOID_H