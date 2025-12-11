#ifndef ZADACI_ZA_VEZBU_CLOCK_H
#define ZADACI_ZA_VEZBU_CLOCK_H
#include <iostream>

class Clock {
protected:
    int hours, minutes, seconds;
    virtual void write(std::ostream &os) const;
public:
    virtual ~Clock() = default;

    Clock(int hours, int minutes,int seconds);

    void set_time(int hours_, int minutes_, int seconds_);

    virtual void operator ++ ();

    friend std::ostream& operator << (std::ostream &os, const Clock &clock);
};


#endif //ZADACI_ZA_VEZBU_CLOCK_H