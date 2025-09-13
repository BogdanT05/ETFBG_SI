#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct part_node {
    char name[11];
    int cnt;
    struct part_node *next;
}part_node_t;

typedef struct price_node {
    char name[11];
    part_node_t *parts;
    struct price_node *next;
} price_node_t;

part_node_t *read_parts(FILE *input) {
    part_node_t *head = NULL;
    part_node_t *last = NULL;
    char c, name[11];

    // pravimo ulanacan listu delova iz jednog reda dok ne dodjemo do tacke.
    while (fscanf(input, "%10s", name) == 1) {
        if (strcmp(name, ".") == 0) break;

        part_node_t *node = malloc(sizeof(*node));
        node->cnt = 1;
        node->next = NULL;

        strcpy(node->name, name);
        if (head == NULL) head = node;
        else last->next = node;

        last = node;
    }
    return head;
}

price_node_t *read_price(FILE *input) {
    price_node_t *node = malloc(sizeof(*node));
    node->next = NULL;
    char name[11];
    // func pravi samo jedan cvor vraca ga ako ga je napravila
    // ako je kraj fajla vraca null
    fscanf(input, "%10s", node->name);

    if (fgetc(input) == EOF){
        free(node);
        return NULL;
    }

    node->parts = read_parts(input);
    return node;
}

price_node_t *read_prices(FILE *input) {
    price_node_t *head = NULL;
    price_node_t *last = NULL;

    // pravimo ulancanu listu cena dok ne dodjemo do kraja fajla
    while (1) {
        price_node_t *node = read_price(input);
        if (node == NULL) break;

        if (head == NULL) head = node;
        else last->next = node;
        last = node;
    }
    return head;
}

part_node_t *agr_parts(part_node_t *parts) {
    part_node_t *head = NULL;
    part_node_t *last = NULL;
    // spajamo cvorove koji se pojavljuju vise puta i sabiramo ih
    for (part_node_t *current = parts; current != NULL; current = current->next) {
        // ponavljanja idu jedno za drugim tako da mozemo to da iskoristimo
        part_node_t *start = current;
        int counter = 1;
        // postavimo prvi elemenet za poredjenje i onda prolazimo sve elemente koji su isti kao on
        // u sl iteraciji prelazimo na sledecu grupu zato sto smo dovoljno pomerili pokazivac
        while (current->next && strcmp(current->next->name, start->name) == 0) {
            counter++;
            current = current->next;
        }

        part_node_t *node = malloc(sizeof(*node));
        node->next = NULL;
        strcpy(node->name, current->name);
        node->cnt = counter;

        if (head == NULL) head = node;
        else last->next = node;
        last = node;
    }
    return head;
}

void print(price_node_t *prices, part_node_t *parts, FILE *output) {
    // prvo kroz sve prices
    for (price_node_t *pr = prices; pr; pr = pr->next) {
        // postavljamo neku nemogucu vrednost dok ne naidjemo na prvi ispravan
        int ans = 1000;
        // onda kroz sve delove prices
        for (part_node_t *r = pr->parts; r; r = r->next) {
            int have = 0;
            // kroz listu parts na kraju
            for (const part_node_t *p = parts; p; p = p->next) {
                // ako je nas potrebni deo u parts onda uzimamo njegov cnt i izlazimo
                if (strcmp(p->name, r->name) == 0) {
                    have = p->cnt;
                    break;
                }
            }
            // kako ce uvek ogranicavajuci faktor biti onaj sa najmanje delove
            // moramo da racunamo njega kao nas odogovr tj broj mogucih nagrada
            if (have < ans) ans = have;
        }

        // ako nikad nismo se pomerili sa nase prvobitne vrednosti znaci da
        // se ta nagrada ne moze dobiti
        if (ans == 1000) ans = 0;
        fprintf(output, "%s %d\n", pr->name, ans);
    }
}

void free_parts(part_node_t *parts) {
    for (part_node_t *current = parts; current!= NULL;) {
        // prvo pomerimo pa oslobodimo
        part_node_t *for_free = current;
        current = current->next;
        free(for_free);
    }
}

void free_prices(price_node_t *prices) {
    for (price_node_t *current = prices; current != NULL;) {
        // svaki price ima svoje parts tako da i njih treba da oslobodimo
        free_parts(current->parts);
        price_node_t *for_free = current;
        current = current->next;
        free(for_free);
    }
}

int main() {
    FILE *f_parts = fopen("tiketi.txt", "r");
    FILE *f_prices = fopen("kombinacije.txt", "r");
    FILE *g = fopen("nagrade.txt", "w");

    part_node_t *parts = read_parts(f_parts);
    price_node_t *prices = read_prices(f_prices);
    part_node_t *ag_parts = agr_parts(parts);
    print(prices, ag_parts, g);

    free_parts(parts);
    free_parts(ag_parts);
    free_prices(prices);

    fclose(f_parts);
    fclose(f_prices);
    fclose(g);
    return 0;
}