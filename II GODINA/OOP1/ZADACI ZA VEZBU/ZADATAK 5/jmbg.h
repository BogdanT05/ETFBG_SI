#ifndef ZADACI_ZA_VEZBU_JMBG_H
#define ZADACI_ZA_VEZBU_JMBG_H
#include <iostream>
#include <string.h>
using namespace std;


class Jmbg {
private:
    char jmbg[14]{};
public:
    explicit Jmbg(const char j[14]) {
        for (int i = 0; i < 14; i++) {
            this->jmbg[i] = j[i];
        }
    }

    friend int compare_jmbg(Jmbg j1, Jmbg j2);
    void write_jmbg() const;
};


#endif //ZADACI_ZA_VEZBU_JMBG_H