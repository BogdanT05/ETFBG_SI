#include "angle.h"

int main() {
    Angle a3(10);
    Angle a4(30, 20, 10);

    Angle a1 = Angle::read_angle();
    Angle a2 = Angle::read_angle();

    a1.add_angles(a2).multiply_angle(2);
    a1.write_angle();
    cout << endl;
    a2.write_angle();
    cout << endl;
    a3.write_angle();
    cout << endl;
    a4.write_angle();

    return 0;
}