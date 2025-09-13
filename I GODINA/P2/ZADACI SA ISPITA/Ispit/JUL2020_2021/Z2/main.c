#include <stdlib.h>
#include <stdio.h>

typedef struct expense {
    int length;
    int *ids;
    double spent;
} TExpense;

typedef struct expenseNode {
    TExpense *data;
    struct expenseNode *next;
} TExpenseNode;

typedef struct user {
    int id;
    double borrowed;
    double payed;
} TUser;

typedef struct userNode {
    TUser *data;
    struct userNode *next;
} TUserNode;

TExpenseNode *read_node(FILE *file) {
    // memorija za sve potrebne pokazivace
    TExpenseNode *node = malloc(sizeof(*node));
    node->data = malloc(sizeof(*node->data));
    node->next = NULL;

    int len;
    // duzina ids, koliko treba id-eva da citamo
    fscanf(file, "%d", &len);

    node->data->length = len;
    // memorija za niz id-eva
    node->data->ids = malloc(len*sizeof(int));

    for (int i = 0; i < len; i++) {
        fscanf(file, "%d", &(node->data->ids[i]));
    }

    fscanf(file, "%lf", &node->data->spent);
    if(fgetc(file) == EOF) return NULL;

    return node;
}

TExpenseNode *read_list(FILE *input) {
    TExpenseNode *head = NULL;
    TExpenseNode *last = NULL;

    while (1) {
        // standradno pravimo ulancanu listu
        // ponavljamo dok nam prva fja ne vrati null
        TExpenseNode *node = read_node(input);
        if (node == NULL){free(node); break;}

        if (head == NULL) head = node;
        else last->next = node;
        last = node;
    }
    return head;
}

TUserNode *create_overview (TExpenseNode *expenses) {
    // idemo redom kroz korisnike i ispitujemo koliko su platili ili su duzni
    // znamo da korisnici idu od 0-10
    TUserNode *head = NULL;
    TUserNode *last = NULL;

    for (int i = 0; i < 11; i++) {
        TUserNode *node = malloc(sizeof(*node));
        node->data = malloc(sizeof(*node->data));
        node->data->id = i;
        double borrowed = 0;
        double payed = 0;

        for (TExpenseNode *current = expenses; current != NULL; current = current->next) {
            for (int j = 0; j < current->data->length; j++) {
                // ako se odgovarajuci korisnik nalazi u data->ids znaci on je ucestvovao ali je idalje duzan
                if (i == current->data->ids[j]) {
                    borrowed = borrowed + current->data->spent/current->data->length;
                }
                // ako se nalazi na prvom mestu znaci da je on platio pa povecamo payed
                if (i == current->data->ids[0]) {
                    payed = payed + current->data->spent/current->data->length;
                }
            }
        }

        // kada prodjemo kroz citavu petlju obuhavatili smo sva pojavljivanja jednog korisnika
        node->data->borrowed = borrowed;
        node->data->payed = payed;
        if (head == NULL) head = node;
        else last->next = node;
        last = node;
    }
    return head;
}

void print_reimbursements(TUserNode *users, FILE *output) {
    for (TUserNode *current = users; current != NULL; current = current->next) {
        // ako su vise duzni nego sto treba da se isplati ne ispisujemo dug nego 0.00
        double diff = current->data->payed - current->data->borrowed;
        if (diff > 0) fprintf(output, "%d %.2lf\n", current->data->id, diff);
        else fprintf(output, "%d %.2lf\n", current->data->id, 0.00);
    }
}

void free_users(TUserNode *users) {
    // freejemo sve pokazivace u TUserNode imamo ih 2
    // TUserNode data i sam TUserNode
    for (TUserNode *current = users; current != NULL;) {
        TUserNode *removal = current;
        current = current->next;
        free(removal->data);
        free(removal);
    }
}

void free_expenses(TExpenseNode *expenses) {
    // imamo 3 pokazivaca TExpenseNode data ids, data i TExpenseNode
    for (TExpenseNode *current = expenses; current != NULL;) {
        TExpenseNode *removal = current;
        current = current->next;
        free(removal->data->ids);
        free(removal->data);
        free(removal);
    }
}

int main() {
    FILE *input = fopen ( "expenses.txt", "r" );
    FILE *output = fopen ( "overview.txt", "w" );

    if ( input == NULL && output == NULL ) {
        return 1;
    }

    TExpenseNode *expenses = read_list ( input );
    TUserNode *users = create_overview ( expenses );
    print_reimbursements ( users, output );

    free_expenses ( expenses );
    free_users ( users );

    fclose ( input );
    fclose ( output );
    return 0;
}