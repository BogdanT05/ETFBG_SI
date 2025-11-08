#include "directory.h"
#include "person.h"

// Kopirajuci konstruktor, smestamo podatke na nove memorijske lokacije
Directory::Directory(Directory &directory) {
    DNode *last = nullptr;
    this->head = nullptr;

    // Pravimo novu ulancanu listu
    for (DNode* current = directory.head; current != nullptr; current = current->next) {
        DNode *node = new DNode;
        node->person = current->person;
        node->next = nullptr;

        if (head == nullptr) head = node;
        else last->next = node;
        last = node;
    }
}

// Pomerajuci konstruktor
Directory::Directory(Directory &&directory) {
    this->head = directory.head;
    directory.head = nullptr;
}

void Directory::add_person(const Person &person) {
    DNode *node = new DNode;
    node->person = person;
    node->next = nullptr;

    DNode *last_node = nullptr;
    DNode *current = this->head;

    // Elemente dodajemo po rastucem rasporedu
    // Kada nadjemo element pre kog treba da ubacimo novi pamtimo
    // Prethodni element i naredni element
    while (current != nullptr) {
        if (compare_jmbg(current->person.jmbg, person.jmbg) > 0) {
            break;
        }

        last_node = current;
        current = current->next;
    }

    // Ako je lista prazna dodajemo ga kao head
    // Ako je last_node == nullptr to znaci da dodajemo na pocetak liste
    if (head == nullptr) head = node;
    if (last_node != nullptr) last_node->next = node;
    node->next = current;
}

void Directory::write_directory() const {
    for (DNode *current = this->head; current != nullptr; current = current->next) {
        current->person.write_name();
    }
}
