#include "song.h"

bool Song::compare_duration(const Song &s1, const Song &s2) {
    return (s1.minutes > s2.minutes) || (s1.minutes == s2.minutes && s1.seconds > s2.seconds);
}

// Kada dodajemo izvodjaca dodajemo ga ako nismo napunili niz
bool Song::add_performer(const Performer& performer) {
    if (this->length == this->capacity) return false;
    performers[length] = performer;
    length++;
    return true;
}

void Song::write_song() const {
    cout << "\tP(" << name << " - " << this->minutes << " : " <<setfill('0') << setw(2) << this->seconds << ")" << endl;
    for (int i = 0; i < length; i++) {
        performers[i].write_performer();
    }
}
