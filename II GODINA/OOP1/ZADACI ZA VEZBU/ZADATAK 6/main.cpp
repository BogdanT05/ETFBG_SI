#include "Complex.h"
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

    c1 = {1/10 + 4/6, 0.5};
    c2 = {46/60.0, 0.5};

    std::cout << "C1 == C2: " <<  (c1 == c2) << std::endl;
    std::cout << "C1 != C2: " <<  (c1 != c2) << std::endl;

    // std::cin >> c1;
    // std::cout << "C1: " << c1;

    complex::Complex c = 3_i;
    std::cout << "C: " << c << std::endl;
}