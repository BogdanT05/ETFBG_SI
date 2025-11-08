#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_row_empty(char **m, int row, int start_column, int length) {
    for (int i = start_column; i < length+start_column; i++) {
        if (m[row][i] != '#') return 0;
    }
    return 1;
}

int is_column_empty(char **m, int column, int start_row, int length) {
    for (int i = start_row; i < length; i++) {
        if (m[i][column] != '#') return 0;
    }
    return 1;
}

char **load_matrix(int *rows, int *columns) {
    scanf("%d %d", rows, columns);
    char **matrix = calloc(*rows, sizeof(*matrix));

    for (int i = 0; i < *rows; i++) {
        matrix[i] = calloc(*columns, sizeof(*matrix[i]));
        for (int j = 0; j < *columns; j++) {
            matrix[i][j] = '#';
        }
    }



    return matrix;
}

void compress(char **m, int *rows, int *columns) {

}

void free_matrix(char **m, int rows) {

}

int main() {
    return 0;
}
