#ifndef ZADACI_ZA_VEZBU_CLOCKWD_H
#define ZADACI_ZA_VEZBU_CLOCKWD_H
#include "Clock.h"

class ClockWD : public Clock {
private:
    int day, month, year;
    int days_in_month(int month_) const;
    void write(std::ostream &os) const override;
public:

    ClockWD(int day, int month, int year, int hours, int minutes, int seconds);
    void set_date(int day_, int month_, int year_);
    void operator ++ () override;
};


#endif //ZADACI_ZA_VEZBU_CLOCKWD_H