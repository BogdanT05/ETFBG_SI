
#ifndef TB240348_LINKED_LIST_H
#define func

typedef struct node {
    int data;
    int w;
    struct node *next;
} Node;

// Kreiranje liste (sa zaglavljem)
Node *form_list(void);

// Oslobadjanje memorije (Unistavanje liste)
void free_list(Node *header);

// Ispis liste (od prvog stvarnog elementa, tj. header->next)
void print_list(Node *header);

// Umetanje na zadatu poziciju (ako ne postoji dodavanje na kraj)
Node *insert_on_position(Node *header, int position);

// Brisanje svih
Node *remove_nodes(Node *header, int del_value);

// Pretrage
void search_first(Node *header, int value);
void search_last(Node *header, int value);
void search_all(Node *header, int value);


typedef struct {
    int n;
    int directed;
    Node **adj;

    char **name;
    char *mountain;
    int *lift;
}Graph;

// Kreiranje grafa sa pocetnim elementima
Graph *form_graph(int n, int directed, char **codes);

// Oslobadjane memorije za graf
void free_graph (Graph *graph);

// Dodavanje cvorova
Graph *add_node(Graph *graph, char *code);

// Brisanje cvorova
Graph *remove_node(Graph *graph, int u);

// Dodavanje grana
Graph *add_edge(Graph *graph, int w, int u, int v);

// Brisanje grana
Graph *remove_edge(Graph *graph, int u, int v);

// Ispis grafa
void print_graph(Graph *graph);

// Pronalazak svih puteva od jedne tacke to svih ostalih
void DFS_finding_routes(Graph *graph, int starting_point);

// Pronalazak najkraceg puta izmedju 2 tacke uz pomoc "dijkstra" algoritma
void dijkstra_shortest_route(Graph *graph, int starting_point, int ending_point);

#endif //TB240348_LINKED_LIST_H