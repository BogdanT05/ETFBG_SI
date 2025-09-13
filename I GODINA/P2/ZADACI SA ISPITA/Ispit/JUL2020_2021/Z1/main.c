#include <stdlib.h>
#include <stdio.h>

int **read_data() {
    int **matrix = NULL;
    int c, p, d, i = 0;
    // pravimo matricu sa nepoznatim brojem vrsta i tri kolone
    while (scanf("%d %d %d\n", &c, &p, &d) == 3) {
        matrix = realloc(matrix, (i+1)*sizeof(*matrix));
        matrix[i] = malloc(3*sizeof(*matrix[i]));
        matrix[i][0] = c;
        matrix[i][1] = p;
        matrix[i][2] = d;
        i++;
    }
    // zadnja vrsta matrice treba da bude NULL
    matrix = realloc(matrix, (i+2)*sizeof(*matrix));
    matrix[i+1] = NULL;
    return matrix;
}

void sort_data(int **data) {
    // bubble sort po kapacitetu sale tj elementima u drugoj koloni
    for (int i = 0; data[i] != NULL; i++) {
        for (int j = i; data[j] != NULL; j++) {
            if (data[i][1] > data[j][1]) {
                int *temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
}

void process_data(int **data) {
    int len = 0;
    // Pronalazimo duzinu matrice
    while (data[len] != NULL) len++;

    sort_data(data);
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            // ako je kapacitet dovoljan onda uklanjamo vrstu iz koje
            // smo prebacili studente i ubacujemo ih u novu salu/vrstu
            if ((data[i][2] + data[j][2]) <= data[j][1] && (i != j)) {
                data[j][2] = data[i][2] + data[j][2];
                free(data[i]);
                // brisemo tu kolonu
                for (int n = i; n < len; n++) {
                    data[n] = data[n+1];
                }
                // smanjujemo duzinu matrice
                len--;
                // vracamo se jedan korak unazad mozda opet treba da izvrsimo obradu nad novom vrstom
                i--;
                // iskacemo ako smo zavrsili jedan ciklus brisanja
                break;
            }
        }
    }
}

void print_data(int **data) {
    for (int i = 0; data[i] != NULL; i++) {
        if (data[i+1] != NULL) {
            for (int j = 0; j < 3; j++) printf("%d%c", data[i][j], (j == 2)?'\n':' ');
        }else printf("%d %d %d", data[i][0], data[i][1], data[i][2]);
    }
}

void free_data(int **data) {
    for (int i = 0; data[i] != NULL; i++) {
        free(data[i]);
    }
    free(data);
}

int main() {
    int **data = read_data();
    process_data(data);
    print_data(data);
    free(data);
    return 0;
}