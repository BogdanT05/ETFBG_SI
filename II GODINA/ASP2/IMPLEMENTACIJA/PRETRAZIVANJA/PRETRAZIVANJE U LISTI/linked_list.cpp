#include "linked_list.h"
#include <iostream>

Linked_list::Linked_list() {head = last = nullptr;}
Linked_list::Linked_list(const Linked_list &list) {
    head = nullptr;
    last = nullptr;
    for (Node *current = list.head; current != nullptr; current = current->next) {
        Node *node = new Node(current->key, current->content);

        if (head == nullptr) head = node;
        else last->next = node;
        last = node;
    }
}

Linked_list::Linked_list(Linked_list &&list) noexcept {
    head = list.head;
    last = list.last;

    list.head = nullptr;
    list.last = nullptr;
}

Linked_list::~Linked_list() {
    for (Node *current = head; current != nullptr;) {
        Node *removal = current;
        current = current->next;
        delete removal;
    }
}

void Linked_list::add_element(int key, int content) {
    Node *node = new Node(key, content);

    if (head == nullptr) head = node;
    else last->next = node;
    last = node;
}

void Linked_list::delete_last() {
    if (head != nullptr) {
        Node *current = head;
        Node *removal = nullptr;
        for (;current->next != last; current = current->next) {}

        current->next = nullptr;
        removal = last;
        last = current;
        delete removal;
    }
    else {
        std::cout << "Lista je prazna!" << std::endl;
    }
}

void Linked_list::write_list() const{
    for (Node *current = head; current != nullptr; current = current->next) {
        std::cout << "[" << current->content << ", " << current->key << "]";
    }
    std::cout << std::endl;
}

// Standardno sekvencijalno pretrazivanje dok ne dodjemo do odg elementa
// Slozenost - O(n)
int Linked_list::sequential_search(int key) const{
    for (Node *current = head; current != nullptr; current = current->next) {
        if (current->key == key) return current->content;
    }
    return -1; // Element ne postoji u listi.
}

// Sekvencijalna pretraga sa granicnikom
// kljuc se dodaje na kraj liste kao granicnik
// Pogodan za ulancanu listu zbog lakseg dodavanja elemenata
int Linked_list::sequential_search_limiter(int key){
    this->add_element(key, 0);
    Node *current;

    for (current = head; current->key != key; current = current->next) {}
    if (current->next == nullptr) {
        this->delete_last();
        return -1;
    }  // ako smo na zadnjem elementu to znaci da key ne postoji u listu

    int exist = current->content;
    this->delete_last(); // Brisemo granicnik da nam ne poremeti sadrzaj liste.
    return exist;

    // U suprotnom vrati odg element
}

// Optimizacije sekvencijalne pretrage tako sto svaki put kada nadjemo kljuc
// Stavljamo ga na pocetak da bi smanjili vreme pretrage
// Ako ponovo trazimo isti kljuc.
// Veoma povoljno u ulancanoj listi zbog jednostavnog prespajanja elemenata, ne toliko u sekvencijalnoj listi
// Veoma radikalno ali pri manjim skupovima podataka poboljsava performanse
int Linked_list::move_to_front_seq_search(int key){
    int exist = -1;
    Node *before = nullptr;
    Node *current = head;

    for (; current != nullptr; current = current->next) {
        if (current->key == key){
            exist = current->content;
            break;
        }
        before = current;
    }

    if (current != nullptr && before != nullptr) {
        // Ako lista ima vise od jednog elementa odna pomeramo napred
        before->next = current->next;
        current->next = head;
        head = current;
        return exist;
    }
    if (before == nullptr && current != nullptr) {
        // Ako je element na prvom mestu ili imamo samo jedan element ne pomeramo nista
        return exist;
    }

    // element ne postoji u listi
    return exist;
}

// Jos jedan metod poboljsavanja performansi jeste transpozicija, tj prilikom
// Pronalaska kljuca guramo ga za jednu poziciju napred tako omogucavamo da
// Se frekventniji elementi probiju napred dok oni redji ne uticu na ostale elemente
// Pogodna za veci skup podataka za 5-10% bolja u odnosu na pomeranje na pocetak
int Linked_list::transposition_seq_search(int key) const{
    Node *before = nullptr;
    int exist = -1;

    for (Node *current = head; current != nullptr; current = current->next){
        if (current->key == key) {
            exist = current->content;
            if (before != nullptr) { // Ako postoji samo jedan element u listi nemamo sta da pomerimo
                int temp = current->key;
                current->key = before->key;
                before->key = temp;

                temp = current->content;
                current->content = before->content;
                before->content = temp;
            }
            return exist;
        }
        before = current;
    }
    return exist;
}
