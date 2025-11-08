#ifndef ZADACI_ZA_VEZBU_DIRECTORY_H
#define ZADACI_ZA_VEZBU_DIRECTORY_H
#include "person.h"

class Directory {
private:
    struct DNode {
        Person person;
        DNode* next;
    };
    DNode *head;
public:
    Directory() {
        head = nullptr;
    }

    Directory(Directory& directory);
    Directory(Directory&& directory);

    void add_person(const Person &person);
    void write_directory() const;

    ~Directory() {
        for (DNode* current = head; current != nullptr;) {
            DNode *removal = current;
            current = current->next;
            delete removal;
        }
    }
};


#endif //ZADACI_ZA_VEZBU_DIRECTORY_H