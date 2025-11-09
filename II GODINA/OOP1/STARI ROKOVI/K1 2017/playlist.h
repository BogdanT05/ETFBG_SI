#ifndef STARI_ROKOVI_PLAYLIST_H
#define STARI_ROKOVI_PLAYLIST_H
#include "song.h"

class Playlist {
private:
    int minutes;
    int seconds;

    // Ulancana lista kako bi omogucili pleylistu "neogranicenog" kapaciteta
    struct SNode {
        Song *song;
        SNode *next;
        explicit SNode(Song *s1, SNode* n = nullptr) {
            song = s1;
            next = n;
        }
    };
    SNode *head;
    SNode *last;
public:
    Playlist() {
        minutes = 0;
        seconds = 0;
        head = nullptr;
        last = nullptr;
    }

    Playlist(Playlist &playlist);
    Playlist(Playlist &&playlist);
    ~Playlist();

    void add_song(Song *song);
    void sort_playlist() const;
    void write_playlist() const;
};


#endif //STARI_ROKOVI_PLAYLIST_H