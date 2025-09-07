#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Graph *form_graph(int n, int directed, char **codes) {

    Graph *graph = calloc(1, sizeof(*graph)); // Prvo prostor za graf
    // Popunjavamo osnovne podatke i oslobadjamo memoriju
    // Svi imaju n elemenata zato sto svaki cvor ima svaki od ovih vrednosti
    graph->adj = calloc(n, sizeof(*graph->adj));
    graph->n = n;
    graph->directed = directed;
    graph->mountain = calloc(n, sizeof(*graph->mountain));
    graph->lift = calloc(n, sizeof(*graph->lift));
    graph->name = calloc(n, sizeof(*graph->name));

    // Pravimo ulancanu listu za svaki pojedinacni cvor
    // Pokazivacemo na sve elemente koji su u vezi sa cvorem na kom radimo
    for (int i = 0; i < n; i++) {
        Node *header = calloc(1, sizeof(*header));
        header->next = NULL;
        graph->adj[i] = header;
    }

    // Popunjavamo podatke
    for (int i = 0; i < n; i++) {
        graph->name[i] = strdup(codes[i]);
        graph->mountain[i] = codes[i][0];
        int lift = codes[i][1] - '0';
        graph->lift[i] = lift;
    }
    return graph;
}

void free_graph (Graph *graph) {
    // Moramo osloboditi svu memoriju koju smo zauzeli za sve elemente grafa
    for (int i = 0; i < graph->n;i++) {
        free_list(graph->adj[i]);
        free(graph->name[i]);
    }
    free(graph->adj);
    free(graph->name);
    free(graph->mountain);
    free(graph->lift);
    free(graph);
}

Graph *add_node(Graph *graph, char *code) {
    int old_size = graph->n;
    int new_size = old_size + 1;

    // Ako dodajemo moramo da povecamo memoriju
    graph->adj = realloc(graph->adj, new_size*sizeof(*graph->adj));
    graph->mountain = realloc(graph->mountain, new_size*sizeof(*graph->mountain));
    graph->lift = realloc(graph->lift, new_size*sizeof(*graph->lift));
    graph->name = realloc(graph->name, new_size*sizeof(*graph->name));

    Node *header = calloc(1 ,sizeof(*header));
    header->next = NULL;
    graph->adj[old_size] = header; // dodajemo novu listu susedstva na poslednje mesto
    // old size zato sto se niz ide od 0 do n-1 pa kad prosirimo za jos +1 poslednji element je na n (old_size)
    graph->name[old_size] = strdup(code);
    graph->mountain[old_size] = code[0];
    int lift_num = code[1] - '0';
    graph->lift[old_size] = lift_num;

    graph->n = new_size;

    return graph;
}

Graph *remove_node(Graph *graph, int u) {
    int last = graph->n - 1; // indeks zadnjeg kad obrisemo element
    free_list(graph->adj[u]);
    graph->adj[u] = NULL; // trebace nam posle zato ga cuvamo iako je prazan

    for (int i = 0; i < graph->n; i++) {
        if (i == u) continue; // u smo vec obrisali gore sad trebamo sva temena koja ulaze u teme koje smo obrisali
        Node *previous = graph->adj[i];
        Node *current = previous->next;
        // Pravimo dva pokazivaca, jedan prati tekuci el a drugi prethodni da bi mogli da ih prespojimo
        while (current) {
            if (current->data == u) { // ako je tim cvorevima element u susjed tj povezani su sa njim treba da obrisemo tu vezu
                previous->next = current->next;
                free(current);
                current = previous->next;
            }else {
                previous = current;
                current = current->next;
            }
        }
    }

    // Da bi ostale podatke obrisali najlakse je da podatke od u prebacimo na kraj liste i onda
    // samim dealociranjem tj smanjenjem memorije grafa mi brisemo ostale podatke
    if (u != last) {
        // na mesto u stavljamo podatke zadnjeg elementa
        graph->adj[u] = graph->adj[last];
        graph->name[u] = graph->name[last];
        graph->mountain[u] = graph->mountain[last];
        graph->lift[u] = graph->lift[last];

        for (int i = 0; i < graph->n; i++) {
            Node *current = graph->adj[i]->next;
            while (current) {
                if (current->data == last) { // Ako smo na zadnjoj poziciji, tu stavljamo podatke od u
                    current->data = u;
                }
                current = current->next;
            }
        }
    }

    // Ako je u vec zadnji element nema potrebe da bilo sta pomeramo samo dealociramo
    if (u == last) free(graph->name[u]);

    graph->n = last;
    graph->adj = realloc(graph->adj, last*sizeof(*graph->adj));
    graph->name = realloc(graph->name, last*sizeof(*graph->name));
    graph->mountain = realloc(graph->mountain, last*sizeof(*graph->mountain));
    graph->lift = realloc(graph->lift, last*sizeof(*graph->lift));

    return graph;
}

Graph *add_edge(Graph *graph, int w, int u, int v) {

    Node *el = calloc(1, sizeof(*el)); // Pravimo prostor za elemente liste susednosti
    el->data = v; // Cvor u koji idemo
    el->w = w; // Tezina

    // el zapravo predstavlja ulancanu listu, samo povezujemo elemente.
    el->next = graph->adj[u]->next;
    graph->adj[u]->next = el;

    return graph;
}

Graph *remove_edge(Graph *graph, int u, int v) {
    Node *previous = graph->adj[u];
    Node *current = previous->next;
    // Takodje uz pomoc dva pokazivaca kao i kod ulancane liste brisemo
    // podatke tako sto prespojimo listu
    while (current) {
        if (current->data == v) {
            previous->next = current->next;
            free(current);
            break;
        }
        previous = current;
        current = current->next;
    }

    return graph;
}

void print_graph(Graph *graph) {
    // Ispisujemo imena (Planina + Zica)
    for (int i = 0; i < graph->n; i++) {
        printf("%s: ", graph->name[i]);

        Node *current = graph->adj[i]->next;
        while (current) {
            // Za svaki cvor ispisujemo sa kim je vezan i njegovu tezinu
            printf(" %s(%d)", graph->name[current->data], current->w);
            current = current->next;
        }
        putchar('\n');
    }
}

void DFS_finding_routes(Graph *graph, int starting_point) {
    // Prolazimo po dubinin na osnovu algoritma sa predavanja
    // Imamo dve liste, poseceni elementi, i "stack"
    // stack je zapravo obicna lista brojeva ali koristimo LIFO
    int *visited = calloc(graph->n, sizeof(*visited));
    int *stack = calloc(graph->n, sizeof(*stack));

    // Na vrh "stacka" stavljamo pocetni cvor, od koga pocinjemo
    int top = 0;
    stack[top] = starting_point;
    top++;

    printf("%s", graph->name[starting_point]);
    while (top>0) { // Ako ima elemenata u stacku idemo kroz stack
        int v = stack[--top];
        if (v != starting_point) { // necemo da ispisemo pocetni element
            printf("->%s", graph->name[v]);
        }

        // Za svakog naslednika idemo u dubinu
        for (Node *current = graph->adj[v]->next; current != NULL; current = current->next) {
            int u = current->data;
            // BITNO: ako smo ga vec posetili necemo opet, smanjujemo vreme izvrsavanja
            if (!visited[u]) {
                visited[u] = 1;
                stack[top] = u; // stavljamo ga na vrh stacka
                top++;
            }
        }
    }
    putchar('\n');
    free(stack);
    free(visited);
}

void dijkstra_shortest_route(Graph *graph, int starting_point, int ending_point) {
    // radimo po algoritmu sa predavanja
    int n = graph->n;
    int INF = 10000000;
    // Potrebne su nam liste dist - svaka od udaljenosti
    // parent - trebaju nam za stampanje, pamtimo temena
    // parent_w - tezina za svaku granu koja nam treba za ispis
    // visited - da li smo posetili to teme
    int *dist = calloc(n, sizeof(*dist));
    int *parent = calloc(n, sizeof(*parent));
    int *parent_w = calloc(n, sizeof(*parent_w));
    char *visited = calloc(n, 1);

    // Pocetne vrednosti
    for (int i = 0; i < n; i++){
        dist[i] = INF;
        parent[i] = -1;
        parent_w[i] = 0;
    }
    dist[starting_point] = 0; // Udaljenost cvora od samog sebe je 0
    for (int i = 0; i < n; i++) {
        int u = -1;
        int best = INF;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < best) { // Trazimo najkracu udaljenost izmedju dva temena
                best = dist[i]; // Pamtimo je, kao i lokaciju
                u = j;
            }
        }

        if (u == -1) break; // Nismo nasli ni jedan put do grafa ako nemamo poklapanje za prethodnu for petlju
        visited[u] = 1; // Oznacavamo da smo posetili taj cvor
        if (u == ending_point) break; // Takodje ako smo stigli do cilja izlazimo

        for (Node *current = graph->adj[u]->next; current != NULL; current = current->next) {
            int v = current->data;
            int w = current->w;
            if (!visited[v] && dist[u] != INF && dist[u] + w < dist[v]) { // Trazimo najmanji zbir tezina
                dist[v] = dist[u] + w; // ako smo nasli smestamo ga u listu za stampanje
                parent[v] =u; // pamtimo lokaciju
                parent_w[v] = w; // pamtimo tezinu
            }
        }
    }

    if (dist[ending_point] == INF) {
        printf("Nema puta od %s do %s", graph->name[starting_point], graph->name[ending_point]);
    }else {
        // cisto za pomoc pri ispisu
        int *path = calloc(n, sizeof(*path));
        int *edge = calloc(n, sizeof(*edge));
        int len = 0;

        for (int i = ending_point; i != -1;i = parent[i]) {
            // idemo unazad da bi zapamtili redosled za stampanje
            path[len] = i;
            edge[len] = parent_w[i];
            len++;
        }

        printf("Najkraci put od %s do %s, %d min\n", graph->name[starting_point], graph->name[ending_point], dist[ending_point]);
        for (int i = len-1; i>=0; i--) {
            // ispisujemo temena koja posecujemo kao i tezinu za svaki od njih
            printf("%s", graph->name[path[i]]);
            if (i>0) {
                printf("-%d->", edge[i-1]);
            }
        }
        putchar('\n');
        free(path);
        free(edge);
    }
    free(dist);
    free(parent);
    free(parent_w);
    free(visited);
}