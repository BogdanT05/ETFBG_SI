#include "Clock.h"
#include <iomanip>

std::ostream &operator<<(std::ostream &os, const Clock &clock) {
    clock.write(os);
    return os;
}

Clock::Clock(int hours, int minutes, int seconds) : hours(0), minutes(0), seconds(0){
    set_time(hours, minutes, seconds);
}

void Clock::set_time(int hours_, int minutes_, int seconds_) {
    this->hours = (hours_ >= 0 && hours_ <= 23)? hours_ : 0;
    this->minutes = (minutes_ >= 0 && minutes_ <= 59)? minutes_ : 0;
    this->seconds = (seconds_ >= 0 && seconds_ <= 59)? seconds_ : 0;
}

void Clock::write(std::ostream &os) const {
    os  << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds << std::endl;
}

void Clock::operator++() {
    seconds++;
    if (seconds >= 60) seconds = 0, minutes++;
    if (minutes >= 60) minutes = 0, hours++;
    if (hours >= 24) hours = 0;
}
