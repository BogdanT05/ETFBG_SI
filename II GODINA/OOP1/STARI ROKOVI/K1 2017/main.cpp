#include "playlist.h"

int main() {
    // Kratko testiranje programa
    Performer p1("Petar", Genre::REP);
    Performer p2("Zika", Genre::POP);
    Performer p3("Lazar", Genre::ROK);

    Song s1("Pesma1", 2, 45, 1);
    Song s2("Pesma2", 3, 5, 2);

    s1.add_performer(p1);
    s2.add_performer(p2);
    s2.add_performer(p3);

    Playlist pl;
    pl.add_song(&s1);
    pl.add_song(&s2);

    Playlist pl1(pl);
    pl.write_playlist();
    cout << endl;
    pl1.write_playlist();
    return 0;
}