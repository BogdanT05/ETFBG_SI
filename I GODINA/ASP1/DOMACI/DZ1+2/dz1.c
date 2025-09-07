#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_menu(void) {
    printf("a. Kreiraj graf\n");
    printf("b. Unisti graf\n");
    printf("c. Dodaj cvor\n");
    printf("d. Ukloni cvor\n");
    printf("e. Dodaj granu\n");
    printf("f. Ukloni granu\n");
    printf("g. Ispisi graf\n");
    printf("h. Odredi sva moguce mesta do kojih se moze doci\n");
    printf("j. Odredi najkraci put izmedju dva mesta\n");
    printf("q. Izlaz\n");
    printf("----------------------------------------\n");
    printf("Izaberi opciju i pritisni ENTER: ");
}

int main() {
    FILE *file = fopen("CableCars5.txt", "r");
    if (!file) return 1; // Ako fajl nije uspesno otvoren

    int n = 0;
    // Potrebno za rad sa grafom
    char *codes[256];
    char code[3];
    char user_input;

    Graph *graph = NULL;
    print_menu();
    while (1) {
        scanf("%c", &user_input);
        if (user_input == 'q') break;
        switch (user_input) {
            case 'a':
                if (graph == NULL) {
                    n = 0;
                    while (fscanf(file, "%2[^,\n]", code)) { // Skeniramo redom iz fajla do zareza
                        codes[n] = strdup(code);
                        n++;
                        int ch = fgetc(file);
                        // Ako je sledeci karakter zarez nastavljamo, ako je novi red zavrsili smo sa unosom temena
                        if (ch == ',') continue;
                        if (ch == '\n' || ch == '\r' || ch == EOF) break;
                    }
                    graph = form_graph(n, 1, codes);
                    printf("Uspesno, unesite sledecu komandu!\n");
                }else {
                    printf("GRESKA, GRAF POSTOJI VEC");
                }
                break;
            case 'b':
                if (graph != NULL) {
                    free_graph(graph);
                    printf("Uspesno, unesite sledecu komandu!\n");
                    graph = NULL;
                }
                else {
                    printf("GRAF NE POSTOJI");
                }
                break;
            case 'c':
                if (graph != NULL) {
                    char node_input[2];
                    printf("Unesite cvor u formatu (A1): ");
                    scanf("%s\n", node_input);
                    graph = add_node(graph, node_input);
                    n++; // Povecavamo broj elemenata grafa
                    printf("Uspesno, unesite sledecu komandu!\n");
                }else {
                    printf("GRAF NE POSTOJI");
                }
                break;
            case 'd':
                if (graph != NULL) {
                    char node_delete[3];
                    printf("Unesite cvor za brisanje u formatu (A1): ");
                    scanf("%s", node_delete);
                    int i = 0;
                    for (; i < n;i++) {
                        if (strcmp(node_delete, codes[i]) == 0) break; // Trazimo poziciju cvora koji treba da obrisemo
                    }
                    graph = remove_node(graph, i);
                    printf("Uspesno, unesite sledecu komandu!\n");
                }else {
                    printf("GRAF NE POSTOJI");
                }
                break;
            case 'e':
                if (graph != NULL) {
                    int user_input_sub;
                    printf("1. Dodaj iz fajla\n");
                    printf("2. Dodaj samostalno\n");
                    printf("------------------------------------------\n");
                    printf("Izaberi opciju i pritisni ENTER: ");
                    scanf("%d", &user_input_sub);
                    char from[3], to[3];
                    int w, u = 0, v = 0;
                    switch (user_input_sub) {
                        case 1:
                            while (fscanf(file, " %2[^-\r\n]-%2[^-\r\n]-%d", from, to, &w) == 3) {
                                // Citamo elemente iz jedne linije fajla koji zadovoljavaju format
                                // Nakon toga pronalazimo njihove pozicije u graphu
                                for (int i = 0; i < graph->n; i++) {
                                    if (strcmp(graph->name[i], from) == 0) u = i;
                                    if (strcmp(graph->name[i], to) == 0) v = i;
                                }
                                graph = add_edge(graph, w, u, v);
                            }
                            break;
                        case 2:
                            int w_new = 0;
                            printf("Unesite granu koju hcoete da dodate (A1-A2): ");
                            scanf(" %2[^-\n]-%2[^-\n]-%d", from, to, &w_new);

                            for (int i = 0; i < graph->n; ++i) {
                                if (strcmp(graph->name[i], from) == 0) u = i;
                                if (strcmp(graph->name[i], to) == 0) v = i;
                            }
                            graph = add_edge(graph, w_new, u, v);
                            break;
                    }
                    printf("Uspesno, unesite sledecu komandu!\n");
                }else {
                    printf("GRAF NE POSTOJI");
                }
                break;
            case 'f':
                if (graph != NULL) {
                    char from[3], to[3];
                    int u = 0, v = 0;
                    printf("Unesite granu koju hcoete da obrisete (A1-A2): ");
                    scanf(" %2[^-\n]-%2[^-\n]", from, to);

                    for (int i = 0; i < graph->n; ++i) {
                        if (strcmp(graph->name[i], from) == 0) u = i;
                        if (strcmp(graph->name[i], to) == 0) v = i;
                    }
                    graph = remove_edge(graph, u, v);
                    printf("Uspesno, unesite sledecu komandu!\n");
                }else {
                    printf("GRAF NE POSTOJI");
                }
                break;
            case 'g':
                if (graph != NULL) {
                    print_graph(graph);
                    printf("Uspesno, unesite sledecu komandu!\n");
                }else {
                    printf("GRAF NE POSTOJI");
                }
                break;
            case 'h':
                if (graph != NULL) {
                    char start[3];
                    int starting_point = 0;

                    printf("Unesite pocetnu zicaru: ");
                    scanf("%s", start);
                    for (int i = 0; i < n; i++) {
                        if (strcmp(start, graph->name[i]) == 0) {
                            starting_point = i;
                            break;
                        }
                    }
                    DFS_finding_routes(graph, starting_point);
                    printf("Uspesno, unesite sledecu komandu!\n");
                }else {
                    printf("GRAF NE POSTOJI");
                }
                break;
            case 'j':
                if (graph != NULL) {
                    char start[3], end[3];
                    int starting_point = 0, ending_point = 0;
                    printf("Unesite zeljene zicare za koje zelite najbrzi put: ");
                    scanf(" %2[^-\n]-%2[^-\n]", start, end);

                    for (int i = 0; i < graph->n; ++i) {
                        if (strcmp(graph->name[i], start) == 0) starting_point = i;
                        if (strcmp(graph->name[i], end) == 0) ending_point = i;
                    }

                    dijkstra_shortest_route(graph, starting_point, ending_point);
                    printf("Uspesno, unesite sledecu komandu!\n");
                }else {
                    printf("GRAF NE POSTOJI");
                }
                break;
            default:
                continue;
        }
    }

    if (graph != NULL) free_graph(graph);
    fclose(file);
    return 0;
}