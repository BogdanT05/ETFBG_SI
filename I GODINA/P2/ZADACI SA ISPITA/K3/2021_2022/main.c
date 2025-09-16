#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
    char *email;
    char date[11];
    int num;
} TData;

typedef struct node {
    TData data;
    struct node *next;
} TNode;

TNode *read_node(FILE *input) {
    char email[64];
    // alociramo prostor za node
    TNode *node = malloc(sizeof(*node));

    if (fscanf(input,"%63s %10s",email , node->data.date) != 2) {
        // ako smo stigli do kraja fajla
        free(node);
        return NULL;
    }

    // kopiramo email u node, namerno kopiramo da nam se ne izgubi adresa
    node->data.email = strdup(email);
    node->next = NULL;
    return node;
}

TNode *read_list(FILE *input) {
    TNode *head = NULL;
    TNode *last = NULL;

    while (1) {
        // pravimo ulancanu listu od cvorova iz prethodne fje
        TNode *node = read_node(input);
        if (node == NULL) {break;}
        if (head == NULL) head = node;
        else last->next = node;
        last = node;
    }
    return head;
}

int find_duplicates(TNode *list, char *email) {
    // prolazimo kroz sve mejlove u listi do sad i gledamo da li se novi mejl nalazi u toj listi
    for (TNode *current = list; current != NULL; current = current->next) {
        if (strcmp(current->data.email, email) == 0) {
            return 0;
        }
    }
    return 1;
}

void increase_counter (TNode *list, char *email) {
    // pronalazimo mejl ciji brojac treba da povecamo
    // bitno je da se taj mejl vec nalazi u listi, znaci brojimo njegova ponavljanja
    for (TNode *current = list; current != NULL; current = current->next) {
        if (strcmp(current->data.email, email) == 0) {
            current->data.num += 1;
        }
    }
}

void sort_lexic(TNode *head) {
    // leksikografski sortiramo putem bubble sorta
    // menjamo i email i vrednosti da se ne bi pomesali pri ispisu
    // redosled liste ostaje isti samo se vrednosti menjaju
    for (TNode *current = head; current != NULL; current = current->next) {
        for (TNode *sub_current = current->next; sub_current != NULL; sub_current = sub_current->next) {
            if (strcmp(current->data.email, sub_current->data.email) > 0) {
                int temp_num = current->data.num;
                current->data.num = sub_current->data.num;
                sub_current->data.num = temp_num;

                char *temp = current->data.email;
                current->data.email = sub_current->data.email;
                sub_current->data.email = temp;
            }
        }
    }
}

TNode *log_users(TNode *first, char date_from[11], char date_to[11]) {
    TNode *head = NULL;
    TNode *last = NULL;
    TNode *node;

    // treba da nadjemo sve mailove izmedju dva datuma sa njihovim pojavljivanjima
    for (TNode *current = first; current != NULL; current = current->next) {
        // proveravamo da li je datum odgovarajuci
        if (strcmp(current->data.date, date_from) >= 0 && strcmp(current->data.date, date_to) <= 0) {
            // da li je duplikat ako jeste povecaj counter ako ne dodaj ga u listu prvi put
            if (find_duplicates(head, current->data.email)) {
                node = malloc(sizeof(*node));
                node->data = current->data;
                node->data.num = 1;
                node->next = NULL;
                if (head == NULL) head = node;
                else last->next = node;
                last = node;
            }else {
                increase_counter(head, current->data.email);
            }
        }
    }

    sort_lexic(head);
    return head;
}

void print_list(TNode *first, char *file_name) {
    // ispisujemo tako da svi osim zadnjeg ispisa imaju \n na kraju
    FILE *output = fopen(file_name, "w");
    for (TNode *current = first; current != NULL; current = current->next) {
        if (current->next != NULL) fprintf(output,"%s %d\n", current->data.email, current->data.num);
        else fprintf(output, "%s %d", current->data.email, current->data.num);
    }
    fclose(output);
}

void free_list(TNode *first) {
    for (TNode *current = first; current != NULL;) {
        TNode *for_free = current;
        current = current->next;
        free(for_free);
    }
}

int main() {
    FILE *dat = fopen("log.txt", "r");
    char date_from[11], date_to[11];

    scanf("%11s", date_from);
    scanf("%11s", date_to);

    if (!dat) {
        return 0;
    }

    TNode *first = read_list(dat);
    TNode *second = log_users(first, date_from, date_to);
    print_list(second, "statistika.txt");

    free_list(first);
    free_list(second);
    fclose(dat);
    return 0;
}