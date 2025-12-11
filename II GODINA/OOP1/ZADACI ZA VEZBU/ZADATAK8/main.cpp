#include "Object.h"
#include "Sphere.h"
#include "Cuboid.h"

int main() {
    std::cout << "Unesite broj predmeta: ";
    int k;
    std::cin >> k;

    auto **objects = new Object *[k];

    char type;
    for (int i = 0; i < k; i++) {

        std::cout << "Enter type of object to create (S, C): ";
        std::cin >> type;

        if (type == 'S') {
            objects[i] = new Sphere;
        }
        else {
            objects[i] = new Cuboid;
        }

        std::cin >> *objects[i];
    }

    for (int i = 0; i < k; i++) {
        std::cout << *objects[i];
        std::cout << "Volume of object: " << objects[i]->volume();
        std::cout << std::endl;
    }

    delete [] objects;
    return 0;
}