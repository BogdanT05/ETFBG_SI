#ifndef STARI_ROKOVI_SONG_H
#define STARI_ROKOVI_SONG_H
#include "performer.h"
#include <iomanip>

class Song {
private:
    string name;
    int minutes;
    int seconds;
    int capacity;
    int length;
    Performer *performers;
public:
    Song (Song &song) = delete;

    // Performers je niz ogranicenog kapaciteta ga pravimo kao obicnu listu, ne ulancanu
    Song (string name, int minute, int second, int capacity) {
        this->name = name;
        this->minutes = minute;
        this->seconds = second;
        this->capacity = capacity;
        this->performers = new Performer[capacity];
        this->length = 0;
    }

    int get_minutes() const {return this->minutes;}
    int get_seconds() const {return this->seconds;}

    static bool compare_duration(const Song &s1, const Song &s2);
    bool add_performer(const Performer& performer);
    void write_song() const;

    ~Song() {
        delete [] this->performers;
    }
};


#endif //STARI_ROKOVI_SONG_H