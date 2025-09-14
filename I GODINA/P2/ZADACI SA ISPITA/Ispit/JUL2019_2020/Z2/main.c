#include <stdio.h>
#include <stdlib.h>

typedef struct data {
    int id;
    double balance;
    int unsuccessfulTransactions;
} TData;

typedef struct node {
    TData *data;
    struct node *next;
} TNode;

TData *read_line(FILE *input) {
    TData *node = malloc(sizeof(*node));
    int c;
    // Proveravamo da li je kraj fajla
    if ((c = fgetc(input)) == EOF) {
        free(node);
        return NULL;
    }

    // ako smo uzeli nesto sto nije \n trebacenam pa vracamo
    if (c != '\n') ungetc(c, input);
    double balance = 0, n;
    int unsuccessful = 0;

    while (1) {
        // u svakoj liniji sabiramo dok ne dodjemo do 0
        fscanf(input , "%lf", &n);
        if (n == 0) break;
        if (balance + n < 0) unsuccessful++;
        else balance = balance + n;
    }

    node->id = 0;
    node->balance = balance;
    node->unsuccessfulTransactions = unsuccessful;
    return node;
}

TNode *read_list(FILE *input) {
    TNode *head = NULL;
    TNode *last = NULL;
    int i = 0;
    while (1) {
        // standardno pravimo ulancanu listu
        TNode *node = malloc(sizeof(*node));
        node->data = read_line(input);
        node->next = NULL;
        if (node->data == NULL) {
            free(node);
            break;
        }
        node->data->id = i;
        i++;

        if (head == NULL) head = node;
        else last->next = node;
        last = node;
    }
    return head;
}

TNode *remove_unsuccessful(TNode *head, int count) {
    TNode *previous = NULL;
    for (TNode *current = head; current != NULL;) {
        if (current->data->unsuccessfulTransactions > count) {
            // ako nije prvi el samo prespajavmo prethodni i sledeci
            if (previous != NULL){
                TNode *removal = current;
                previous->next = current->next;
                current = current->next;
                free(removal->data);
                free(removal);
            }else{
                // ako je prvi pomeramo head
                TNode *removal = current;
                current = current->next;
                head = current;
                free(removal->data);
                free(removal);
            }
            continue;
        }
        previous = current;
        current = current->next;

    }
    return head;
}

void print(TNode *head) {
    for (TNode *current = head; current != NULL; current = current->next) {
        printf("%d %.2lf %d\n", current->data->id, current->data->balance, current->data->unsuccessfulTransactions);
    }
}

void free_list(TNode *head) {
    for (TNode *current = head; current != NULL;) {
        TNode *removal = current;
        current = current->next;
        free(removal->data);
        free(removal);
    }
}

int main() {
    FILE *input = fopen("transakcije.txt", "r");
    TNode *head = read_list (input);
    head = remove_unsuccessful(head, 1);
    print(head);
    fclose (input);
    free_list(head);
    return 0;
}