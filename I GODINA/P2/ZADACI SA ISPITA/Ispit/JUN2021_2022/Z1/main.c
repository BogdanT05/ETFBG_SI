#include <stdio.h>
#include <stdlib.h>

int **read_matrix(int *n) {
    int **matrix;
    scanf("%d", n);
    matrix = malloc(*n*sizeof(*matrix));

    // standardno ucitavanje prostora i matrice
    for (int i = 0; i < *n; i++) {
        matrix[i] = malloc(10*sizeof(*matrix[i]));
        for (int j = 0; j < 10; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    return matrix;
}

int **form_matrix(int **matrix, int n) {
    // mapiramo poene koje cemo da dodeljujemo
    int points[11] = {1, 2 , 3, 4, 5, 6, 7, 8, 10, 12};
    int **f_matrix = malloc(n*sizeof(*f_matrix));
    // pravimo prvo praznu kvadratnu matricu
    for (int i = 0; i < n; i++) {
        f_matrix[i] = calloc(n, sizeof(*f_matrix[i]));
    }

    for (int i = 0; i < n; i++) {
        // iz pocetne matrice redom citamo kome treba da dodelimo poene
        for (int j = 0; j < 10; j++) {
            // vrsta je odredjena vrednosti iz prvobitne matrice
            // a kolona je mesto na koje treba da stavimo i odredjena je a i
            // zato sto prva drzava treba da njeni poeni budu prvi u svakoj vrsti
            // broj poena uzimamo iz liste points
            f_matrix[matrix[i][j]][i] = points[j];
        }
    }

    return f_matrix;
}

void write_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d%c", matrix[i][j], (j == n-1)?'\n':' ');
        }
    }
}

void free_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int n, **matrix, **newMatrix;
    matrix = read_matrix(&n);
    newMatrix = form_matrix(matrix, n);
    write_matrix(newMatrix, n);

    free_matrix(matrix, n);
    free_matrix(newMatrix, n);
    return 0;
}