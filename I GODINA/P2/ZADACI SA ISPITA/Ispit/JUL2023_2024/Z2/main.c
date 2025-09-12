#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct task_info {
    char name[51];
    int priority;
    int day;
    int month;
    int year;
} TData;

typedef struct task {
    TData data;
    struct task *subtasks;
    struct task *next;
} TNode;

TNode *read_node(FILE *input);

TNode *read_list(char *dat_file) {
    // Pravimo ulancanu listu putem rekurzije
    TNode *head = NULL;
    TNode *last = NULL;
    TNode *node;
    FILE *file_name = fopen(dat_file, "r");

    if (!file_name) return NULL;

    // func read_node ce otici u dubinu koliko je god moguce za glavni task
    // Na kraju ce node zapravo samo jedan element ulancane liste / prvi el
    while ((node = read_node(file_name)) != NULL) {
        node->next = NULL;
        if (head == NULL) { // ako smo na prvom elementu
            head = node;
        }
        else last->next = node;
        last = node;
    }

    fclose(file_name);
    return head;
}

TNode *read_node (FILE *input) {
    int pr, day, mth, y;
    char task_name[51], subtask_name[51]; // podaci koje treba da citamo

    TData data;
    TNode *node = malloc(sizeof(*node)); // pravimo prostor

    if (fscanf(input, "%50s %d %2d.%2d.%4d. %50s", task_name, &pr, &day, &mth, &y, subtask_name) == 6) { // iz fajla skeniramo sve potrebno
        strcpy(data.name, task_name);
        data.priority = pr;
        data.day = day;
        data.month = mth;
        data.year = y;
        node->data = data;
        // stavljamo da sve bude null zato sto ne znamo da li postoje ti elementi
        node->next = NULL;
        node->subtasks = NULL;

        if (strcmp(subtask_name, "X") != 0) {
            node->subtasks = read_list(subtask_name); // ako postoji podtask pozivamo funkciju read_list
        }                                             // funckija read_list poziva read_node i tako u krug
        return node;                                  // dok ne dodjemo do dna nakon toga se postepeno vracamo
    }                                                 // jako dobar primer naizmenicne rekurzije

    free(node);
    return NULL;
}

void print_list(TNode *head, FILE *output) {
    static int level = 0; // brojac dubine (koliko indentationa nam treba)
    for (TNode *current = head; current != NULL; current = current->next) {
        for (int i = 0; i < level; i++) fprintf(output,"    "); // sto smo dublje to vise indentationa
        fprintf(output,"%d %s (%d.%d.%4d.)\n",
        current->data.priority,
        current->data.name,
        current->data.day,
        current->data.month,
        current->data.year);

        if (current->subtasks != NULL) {
            // ako trebamo jos u dubinu povecavamo level i ponovo pozivamo func
            // na kraju smanjujemo level zato sto smo izasli iz dubine
            level++;
            print_list(current->subtasks, output);
            level--;
        }
    }
}

void free_list(TNode *head) {
    for (TNode *current = head; current != NULL; current = current->next) {
        if (current->subtasks != NULL) free_list(current->subtasks); // oslobadjamo iz dubine ka gore
        free(current);
    }
}

int main() {
    TNode *list = read_list("tasks.txt");
    FILE *output = fopen("ispis.txt", "w");
    print_list(list, output);
    free_list(list);
    return 0;
}