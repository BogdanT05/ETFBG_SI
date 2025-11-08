#include "angle.h"

Angle Angle::read_angle(){
    int x;
    cout << "Radijani ili stepeni(minute, sekunde) 1/2: ";
    cin >> x;
    int rad;

    if (x == 2) {
        int deg, min, sec;
        cin >> deg >> min >> sec;
        return Angle(deg, min, sec);
    }else {
        cin >> rad;
        return Angle(rad);
    }
}

void Angle::write_angle() const {
    cout << "Ugao u radijanima: " << this->radians << endl;
    cout << "Ugao u stepenima: " << get_degrees() <<" "<<get_minutes()  <<" "<<get_seconds() << endl;
}
