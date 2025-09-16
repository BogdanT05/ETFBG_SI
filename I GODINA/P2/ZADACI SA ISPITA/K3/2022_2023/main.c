#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int ip[4];
    double bytes;
} data_t;

typedef struct node {
    data_t *data;
    struct node *next;
} node_t;

data_t *read_request(FILE *input) {
    int c;
    // prostor
    data_t *data = malloc(sizeof(*data));

    // ako smo stigli do kraja fajla
    if ((c = fgetc(input)) == EOF){
        free(data);
        return NULL;
    }
    // da ne izgubimo bitan karakter
    if (c != '\n') ungetc(c, input);
    double size;
    char format[3];

    // citamo iz fajla potrebne informacije
    fscanf(input,"%d.%d.%d.%d %lf%2s"
        , &data->ip[0]
        , &data->ip[1]
        , &data->ip[2]
        , &data->ip[3]
        , &size
        , format);

    // konvertujemo mb i kb u bytes
    if (strcmp("MB", format) == 0) size = size * 1000 * 1000;
    else size = size * 1000;
    data->bytes = size;

    return data;
}

node_t *read_requests(FILE *input) {
    node_t *head = NULL;
    node_t *last = NULL;

    // pravimo ulancanu listu
    while (1) {
        node_t *node = malloc(sizeof(*node));
        node->data = read_request(input);
        node->next = NULL;

        // ako je kraj ne zelimo da zaboravimo ovaj prostor koji smo alocirali
        if (node->data == NULL) {
            free(node);
            break;
        }

        if (head == NULL) head = node;
        else last->next = node;
        last = node;
    }

    return head;
}

void sort(node_t *head) {
    // top 5 najgorih srotiranja ikad :)
    // bubble sort manuelno proveravamo za svaki dio ip adresse
    for (node_t *current = head; current != NULL; current = current->next) {
        for (node_t *sub_current = current->next; sub_current != NULL; sub_current = sub_current->next) {
            if (current->data->ip[0] > sub_current->data->ip[0]) {
                data_t *temp = current->data;
                current->data = sub_current->data;
                sub_current->data = temp;

            }else if (current->data->ip[0] == sub_current->data->ip[0]) {
                if (current->data->ip[1] > sub_current->data->ip[1]) {
                    data_t *temp = current->data;
                    current->data = sub_current->data;
                    sub_current->data = temp;

                }else if (current->data->ip[1] == sub_current->data->ip[1]) {
                    if (current->data->ip[2] > sub_current->data->ip[2]) {
                        data_t *temp = current->data;
                        current->data = sub_current->data;
                        sub_current->data = temp;

                    }else if (current->data->ip[2] == sub_current->data->ip[2]) {
                        if (current->data->ip[3] > sub_current->data->ip[3]) {
                            data_t *temp = current->data;
                            current->data = sub_current->data;
                            sub_current->data = temp;
                        }
                    }
                }
            }
        }
    }
}

void compress_requests(node_t *head) {
    for (node_t *current = head; current != NULL;) {
        // sabijamo listu sa 2 pomocna pokazivaca
        node_t *start = current;
        node_t *sub_current = current->next;
        while (sub_current != NULL
            && sub_current->data->ip[0] == start->data->ip[0]
            && sub_current->data->ip[1] == start->data->ip[1]
            && sub_current->data->ip[2] == start->data->ip[2]
            && sub_current->data->ip[3] == start->data->ip[3]) {
            // ako je uslov ispunjen sabiramo bajtove i brisemo iz liste onaj koji smo sabrali
            start->data->bytes += sub_current->data->bytes;
            node_t *removal = sub_current;
            sub_current = sub_current->next;
            free(removal->data);
            free(removal);
        }
        // prespajamo listu nakon sto sve sabijemo
        start->next = sub_current;
        // prelazimo na sledecu grupu
        current = sub_current;
    }
}

void print_requests(node_t *head) {
    for (node_t *current = head; current != NULL; current = current->next) {
        printf("%d.%d.%d.%d %.2lf%s",
            current->data->ip[0],
            current->data->ip[1],
            current->data->ip[2],
            current->data->ip[3],
            current->data->bytes,
            // korisno za ispis nicega moze se koristiti string, a char ne moze
            (current->next != NULL)?"\n":"");
    }
}

void free_requests(node_t *head) {
    for (node_t *current = head; current != NULL;) {
        node_t *removal = current;
        current = current->next;
        free(removal->data);
        free(removal);
    }
}

int main(){
    FILE *input = fopen("requests.txt", "r");
    if (!input) return 0;

    node_t *list = read_requests(input);
    sort(list);
    compress_requests(list);
    print_requests(list);

    free_requests(list);
    fclose(input);
    return 0;
}
