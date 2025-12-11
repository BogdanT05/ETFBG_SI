#include "ClockWD.h"
#include <iomanip>


int ClockWD::days_in_month(int month_) const {
    switch (month_) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
                return 29;
            return 28;
        default:
            return -1;
    }
}


ClockWD::ClockWD(int day, int month, int year, int hours, int minutes, int seconds) : Clock(hours, minutes, seconds) {
    set_date(day, month, year);
}

void ClockWD::set_date(int day_, int month_, int year_) {
    this->year = (year_ > 1950 && year_ <= 2100)? year_ : 2025;
    this->month = (month_ > 0 && month <= 12)? month_ : 1;
    this->day = day_ > 0 && day_ <= days_in_month(month)? day_ : 1;
}

void ClockWD::write(std::ostream &os) const{
    os << day << "." << month << "." << year << " ";
    Clock::write(os);
}

void ClockWD::operator++() {
    Clock::operator++();
    if (hours == minutes && minutes == seconds && seconds == 0) day++;
    if (day > days_in_month(month)) day = 1, month++;
    if (month > 12) month = 1, year++;
}



