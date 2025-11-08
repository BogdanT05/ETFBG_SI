#include "cuboid.h"
/*Klasa kvadar treba da sadrzi tako da ukupna zapremina
 *svih napravljenih kvadara ne prelazi maksimalnu zapreminu
 *omoguciti:
 *postavljanje i dohvatanje maks zapremine
 *dohvatanje trenutne zapremine svih kvadara
 *stvaranje kvadra zadatih ivica
 *citanje kvadra s glavnog ulaza, dohvatanje ivica
 *izracunavanje zapremine i ispis na glavnom izlazu.
 */

int main() {
    Cuboid::set_max_volume(100);
    struct CNode {
        Cuboid *cuboid;
        CNode *next;
    };

    for (char c = 'd'; c == 'd'; cout << "d za nastavak, n za kraj", cin >> c) {
        CNode *head = nullptr;
        CNode *last = nullptr;

        while (true) {
            Cuboid* cub = Cuboid::read_cuboid();
            if (cub == nullptr) break;

            CNode* node = new CNode;

            node->cuboid = cub;
            node->next = nullptr;

            if (head == nullptr) head = node;
            else last->next = node;
            last = node;
        }

        cout << "Zapremine: ";
        for (CNode *current = head; current != nullptr; current = current->next) {
            cout << current->cuboid->calculate_volume() << " ";
        }
        cout << endl;
        cout << "Ukupna zapremina: " << Cuboid::get_total_volume();

        for (CNode *current = head; current != nullptr;) {
            CNode *removal = current;
            current = current->next;

            delete removal->cuboid;
            delete removal;
        }
        cout << endl;
    }



    return 0;
}