#ifndef ETFBG_SI_PERFORMER_H
#define ETFBG_SI_PERFORMER_H
#include <iostream>
#include <cstring>
using namespace std;
enum Genre{POP, REP, ROK};

class Performer {
private:
    string name;
    Genre genre;
    static string genres[4];
public:
    Performer() = default;
    Performer(string name, Genre genre) {
        this->name = name;
        this->genre = genre;
    }

    Genre get_genre() const{return this->genre;}
    void write_performer() const;
};

#endif //ETFBG_SI_PERFORMER_H