#include <iostream>
#include "linked_list.h"
#include "sorted_list.h"

// Sekvencijalna pretraga u nesortiranoj lisiti se odnosti na sve pretrage
// Za ulancanu listu dok je moguce neke od metoda primeniti i na sekvencijalnoj listi
// Generalno je efikasnije taj proces raditi sa ulancanim listama

// Sekvencijalna pretraga u uredjenim listama, razmatramo u okviru
// Sekvencijalnih listi zato sto su efikasnije u ovom slucaju.


int main() {
    Linked_list llist;
    llist.add_element(1,25);
    llist.add_element(5,35);
    llist.add_element(3,53);
    llist.add_element(7,54);
    llist.add_element(4,15);
    llist.write_list();

    std::cout << "Nesortirana ulancana lista: " << std::endl;
    std::cout<<llist.sequential_search(5) << std::endl;
    std::cout<<llist.sequential_search_limiter(1) << std::endl;
    std::cout<<llist.move_to_front_seq_search(7) << std::endl;
    std::cout<<llist.transposition_seq_search(4) << std::endl;

    int list[10] = {1, 3, 5, 7, 10, 12, 15, 20, 25, 100};
    int length = 10;
    int keys[3] = {5, 12, 25};

    std::cout << "Sortirana sekvencijalna lista: " << std::endl;
    std::cout<<sorted_seq_search(list, keys[0], length)<< std::endl;
    std::cout<<binary_search(list, keys[1], length) << std::endl;
    std::cout<<interpolation_search(list, keys[2], length) << std::endl;

    return 0;
}