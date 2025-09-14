#include <stdlib.h>
#include <stdio.h>

char **read_board(int *n) {
    scanf("%d", n);
    char **board = malloc(*n*sizeof(*board));

    for (int i = 0; i < *n; i++) {
        board[i] = malloc(*n*sizeof(*board[i]));
        for (int j = 0; j < *n; j++) {
            // mora ovaj space pre %c da bi preskocili belinu iz prethodnog reda
            scanf(" %c", &board[i][j]);
        }
    }

    return board;
}

int count_in_row(char **board, int row, int n, char c) {
    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (board[row][i] == c) counter++;
    }

    return counter;
}

int count_in_col(char **board, int col, int n, char c) {
    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (board[i][col] == c) counter++;
    }

    return counter;
}

int count_in_diag_main(char **board, int n, char c) {
    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (board[i][i] == c) counter++;
    }

    return counter;
}

int count_in_diag_minor(char **board, int n, char c) {
    int counter = 0;
    // sporedna dijagonala ide od vecih indeksa ka manjem
    for (int i = n-1; i >= 0; i--) {
        if (board[i][i] == c) counter++;
    }
    return counter;
}

int process(char **board, int n) {
    // prvo proveravamo ima li pobednika prebrojavanjem svake vrste i kolone
    for (int i = 0; i < n; i++) {
        if (count_in_row(board, i, n, 'X') == n ||
            count_in_col(board, i, n, 'X') == n ||
            count_in_diag_main(board, n, 'X') == n ||
            count_in_diag_minor(board, n, 'X') == n) return 0;

        if (count_in_row(board, i, n, 'O') == n ||
           count_in_col(board, i, n, 'O') == n ||
           count_in_diag_main(board, n, 'O') == n ||
           count_in_diag_minor(board, n, 'O') == n) return 2;
    }
    int sum_x = 0;
    int sum_o = 0;

    // ako nema pobednika broj pojavljivanja x i o
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'X') sum_x++;
            if (board[i][j] == 'O') sum_o++;
        }
    }

    if (sum_x == sum_o) return 1;
    else return 3;
}

void free_board(char **board, int n) {
    for (int i = 0; i < n; i++) free(board[i]);
    free(board);
}

int main() {
    int n;
    char **board = read_board(&n);
    switch (process(board, n)) {
        case 0:
            printf("POBEDNIK: X");
            break;
        case 1:
            printf("NA POTEZU: X");
            break;
        case 2:
            printf("POBEDNIK: O");
            break;
        case 3:
            printf("NA POTEZU: O");
            break;
        default:
            break;
    }
    free_board(board, n);
    return 0;
}