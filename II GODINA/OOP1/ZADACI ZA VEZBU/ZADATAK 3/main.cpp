#include "queue.h"
#include <cstdlib>

/*Napraviti klasu red i omoguciti sledece funkcije
 *Stvaranje praznog reda sa zadatim kapacitetom
 *Stvaranje kopije drugog reda, unistavanje reda
 *Dodavanje jednog podatka u red, uzimanje podatka iz reda
 *ispitivanje da li je red pun ili prazan
 *ispis reda, i praznjenje reda, glavna funkcija
 */

int main() {
    Queue* queue = new Queue(5);
    while (true) {
        cout << "1. Stvaranje reda\n" <<
                "2. Stavljanje podatka u red\n" <<
                "3. Uzmi podatak iz reda\n" <<
                "4. Ispis reda\n" <<
                "5. Ocisti red\n" <<
                "0. Izlaz" << endl;

        int choice; cin >> choice;
        switch (choice) {
            case 0:
                exit(0);
            case 1:
                delete queue;
                int c;
                cout << "Unesite kapacitet: "; cin >> c;
                queue = new Queue(c);
                break;
            case 2:
                int num;
                cout << "Unesite podatak: "; cin >> num;
                if (!queue->is_full()) queue->push_data(num);
                else exit(1);
                break;
            case 3:
                if (!queue->is_empty()) cout << "Vas podatak je: " << queue->pop_data() << endl;
                else exit(2);
                break;
            case 4:
                queue->write_queue();
                break;
            case 5:
                queue->empty_queue();
                break;
            default:
                break;
        }
    }
    return 0;
}