#include "playlist.h"

// Pravimo ulancanu listu na standardan nacin
void Playlist::add_song(Song *song) {
    SNode *node = new SNode(song);
    if (head == nullptr) head = node;
    else last->next = node;
    last = node;

    minutes += song->get_minutes() + (seconds+song->get_seconds())/60;
    seconds += song->get_seconds() % 60;
}

// Bubble sort za vremensko sortiranje
void Playlist::sort_playlist() const {
    for (SNode *current = head; current->next != nullptr; current = current->next) {
        for (SNode *sub_current = current->next; sub_current != nullptr; sub_current = sub_current->next) {
            if (Song::compare_duration(*current->song, *sub_current->song)) {
                Song *temp = current->song;
                current->song = sub_current->song;
                sub_current->song = temp;
            }
        }
    }
}

void Playlist::write_playlist() const {
    cout << "Lista - trajanje: " << minutes << " : " <<setfill('0') << setw(2) << seconds << endl;
    for (SNode *current = head; current != nullptr; current = current->next) {
        current->song->write_song();
    }
}

// Kopirajuci konstruktor pravimo na novim memorijskim lokacijama novu ulancanu listu
Playlist::Playlist(Playlist &playlist) {
    minutes = playlist.minutes;
    seconds = playlist.seconds;
    head = nullptr;
    last = nullptr;

    for (SNode *current = playlist.head; current != nullptr; current = current->next) {
        SNode *node = new SNode(current->song);
        if (head == nullptr) head = node;
        else last->next = node;
        last = node;
    }
}

// Kopirajuci konstruktor stare pokazivace vracamo na nullptr
Playlist::Playlist(Playlist &&playlist) {
    minutes = playlist.minutes;
    seconds = playlist.seconds;
    head = playlist.head;
    last = playlist.last;

    playlist.head = nullptr;
    playlist.last = nullptr;
}

Playlist::~Playlist() {
    // Oslobadjamo memoriju koju zauzima ulancana lista
    for (SNode *current = head; current != nullptr;) {
        SNode *remove = current;
        current = current->next;
        delete remove;
    }
}