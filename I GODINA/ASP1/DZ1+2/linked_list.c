#include <stdlib.h>
#include <stdio.h>
#include "func.h"

Node *form_list() {
    Node *header = calloc(1, sizeof(*header));
    Node *last = header;

    int value = 0;
    while (scanf("%d", &value) == 1) {
        // kada radimo sa zaglavljem ne moramo da brinemo o poziciji
        // prvog elementa zato sto uvek znamo adresu headera, prvi je header->next
        Node *node = calloc(1, sizeof(*node));
        node->data = value;
        node->next = NULL;

        last->next = node;
        last = node;
    }

    return header;
}

void free_list(Node *header) {
    // brisemo sve ukljucujuci i header
    for (Node *current = header; current != NULL;) {
        Node *removal = current;
        current = current->next;
        free(removal);
    }
}

void print_list(Node *header) {
    // printujemo od prvog pravog elementa, header->next
    for (Node *current = header->next; current != NULL; current = current->next) {
        printf("%d->", current->data);
    }
    printf("NULL\n");
}

Node *insert_on_position(Node *header, int position) {
    int counter = 0;
    int value;

    printf("Unesite vrednost koju hocete da unesete na poziciju : ");
    scanf("%d", &value);

    Node *previous = NULL;
    Node *current = header->next;

    Node *new_node = calloc(1, sizeof(*new_node));
    new_node->data = value;
    new_node->next = NULL;

    for (;current != NULL; current = current->next) {
        // pamtimo poziciju prethodnog da bi mogli da ih povezemo
        // prethodni -> novi -> sledeci
        if (counter == position) {
            if (previous != NULL) {
                previous->next = new_node;
                new_node->next = current;
            }else {
                // ako dodajemo na prvo mesto
                header->next = new_node;
                new_node->next = current;
            }
            return header;
        }
        counter++;
        previous = current;
    }
    // ako dodajemo na zadnje mesto, tada previous ce biti zadnji
    // previous -> next povezujemo novi cvor na kraj
    previous->next = new_node;
    return header;
}

Node *remove_nodes(Node *header, int del_value) {
    Node *current = header->next;
    Node *previous = NULL;
    Node *for_removal = NULL;

    while (current != NULL) {
        for_removal = NULL;
        if (current->data == del_value) {
            for_removal = current; // pamtimo adresu za brisanje
            previous->next = current->next;
        }else {
            previous = current;
        }
        current = current->next; // nakon sto odemo sa elementa koji treba da obrisemo onda free
        free(for_removal);
    }

    return header;
}

void search_first(Node *header, int value) {
    int counter = 0;
    int position = 0;
    int exist = 0;
    for (Node *current = header->next; current != NULL; current = current->next) {
        if (current->data == value) {
            // izlazimo cim nadjemo potrebni element
            position = counter;
            exist = 1;
            break;
        }
        counter++;
    }

    if (!exist) {
        printf("Taj element ne postoji u listi!");
    }else {
        printf("Prvo pojavljivanje tog elementa je na poziciji: %d", position);
    }
}

void search_last(Node *header, int value) {
    int counter = 0;
    int position = 0;
    int exist = 0;
    for (Node *current = header->next; current != NULL; current = current->next) {
        // cuvamo poziciju zadnjeg pronalaska
        if (current->data == value) {
            position = counter;
            exist = 1;
        }
        counter++;
    }
    if (!exist) {
        printf("Taj element ne postoji u listi!");
    }else {
        printf("Poslednje pojavljivanje tog elementa je na poziciji: %d", position);
    }
}

void search_all(Node *header, int value) {
    int counter = 0;
    for (Node *current = header->next; current != NULL; current = current->next) {
        if (current->data == value) {
            counter++;
        }
    }
    if (!counter) {
        printf("Taj element ne postoji u listi!");
    }else {
        printf("Taj element se pojavljuje %d puta", counter);
    }
}