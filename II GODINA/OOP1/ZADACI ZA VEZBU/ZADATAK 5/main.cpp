#include "directory.h"

int main() {
    Directory dir;
    // dir.add_person(Person("Marko", Jmbg("1205986110022")));
    // dir.add_person(Person("Milan",Jmbg("3112969235052")));
    // dir.add_person(Person("Zoran",Jmbg("1511990872035")));
    // dir.add_person(Person("Petar",Jmbg("0207000345678")));
    // dir.add_person(Person("Stevo",Jmbg("2503973123024")));

    dir.add_person(Person("Marko", Jmbg("a")));
    dir.add_person(Person("Milan",Jmbg("d")));
    dir.add_person(Person("Zoran",Jmbg("e")));
    dir.add_person(Person("Petar",Jmbg("b")));
    dir.add_person(Person("Stevo",Jmbg("c")));

    dir.write_directory();
    return 0;
}