#include <iostream>

#include "ClockWD.h"

int main() {
    std::cout << "Enter number of clocks: ";

    int k;
    std::cin >> k;

    auto **clocks = new Clock*[k];

    int has_date;
    for (int i = 0; i < k; i++) {
        std::cout << "With date or not (1 | 0)?: ";
        std::cin >> has_date;

        int year, month, day, hours, minutes, seconds;
        if (has_date) {
            std::cout << "Enter year, day, month: ";
            std::cin >> year >> month >> day;
        }

        std::cout << "Enter hours, minutes, seconds: ";
        std::cin >> hours >> minutes >> seconds;

        if (has_date) clocks[i] = new ClockWD(day, month, year, hours, minutes, seconds);
        else clocks[i] = new Clock(hours, minutes, seconds);
    }

    for (int i = 0; i < k; i++) {
        std::cout << *clocks[i] << std::endl;
    }

    delete [] clocks;
    return 0;
}