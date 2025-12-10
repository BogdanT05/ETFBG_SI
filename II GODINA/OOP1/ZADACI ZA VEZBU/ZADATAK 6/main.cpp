#include "Iterator.h"
using complex::operator ""_i;

int main() {
    complex::Complex c1 {1, -2}, c2{2, 3};

    // Tesitranje funkcionalnosti

    std::cout << real(c1) << " | " << imaginary(c1) << std::endl;
    std::cout << "C1: " << c1 << std::endl;
    std::cout << "C2: " << c2 << std::endl;
    std::cout << "C1 * C2: " << (c1*c2) << std::endl;
    std::cout << "C1 after modification: " << c1 << std::endl;
    std::cout << "abs(C1): " << abs(c1) << std::endl;
    std::cout << "arg(C1): " << arg(c1) << std::endl;
    std::cout << "~C1: " << ~c1 << std::endl;

    c1 = {1/10.0 + 4/6.0, 0.5};
    c2 = {46/60.0, 0.5};

    std::cout << "C1 == C2: " <<  (c1 == c2) << std::endl;
    std::cout << "C1 != C2: " <<  (c1 != c2) << std::endl;

    // std::cin >> c1;
    // std::cout << "C1: " << c1;

    complex::Complex c = 3_i;
    std::cout << "C: " << c << std::endl;

    Array a, b;
    a[0] = {1, 2};
    a[1] = {3, 4};
    a[2] = {1,2};

    std::cout << a[1] << std::endl;
    b = a;
    std::cout << b[1] << std::endl;

    std::cout << "Found at index: " << a({1, 2}) << std::endl;
    std::cout << "Found at index: " << a({0, 0}) << std::endl;
    std::cout << "Found at index: " << a({1, 2}, 4, 1) << std::endl;

    Iterator iterator = a.get_iterator();
    for (int i = 0; i < a.get_capacity(); i++) {
        a[i] = complex::Complex(i+3, i*2-1);
    }

    while (iterator) {
        std::cout << "(" << iterator->get_real() << ", " << iterator->get_imaginary() << ") | ";
        std::cout << *iterator << std::endl;
        ++iterator;
    }

    return 0;
}