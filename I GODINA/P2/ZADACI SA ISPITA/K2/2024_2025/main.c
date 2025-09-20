#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *read_line() {
    char c;
    char *line = NULL;
    int i = 0;

    // provera da li je prazan unos
    if ((c = getchar()) == '\n') return "";
    ungetc(c, stdin);

    while (1) {
        c = getchar();
        if (c == '\n') break;

        // ne zelimo brojeve u nasem stringu ali ne zelimo da zaboravimo blanko znak
        if (c-'0'> 9 || c == ' ') {
            line = realloc(line, (i+2)*sizeof(*line));
            line[i] = c;
            i++;
        }
    }

    line[i] = '\0';
    return line;
}

char **read_lines() {
    char **lines = malloc(sizeof(*lines));
    int i = 0;

    // citamo svaku liniju redom dok ne bude prazno
    while (1) {
        char *line = read_line();
        if (strcmp(line, "") == 0) break;
        lines = realloc(lines, (i+2)*sizeof(*lines));
        lines[i] = line;
        i++;
    }

    lines[i] = NULL;
    return lines;
}

void encode(char **lines, int shift) {
    if (shift > 26) shift = shift % 26;

    for (int i = 0; lines[i] != NULL; i++) {
        for (int j = 0; j < strlen(lines[i]); j++) {
            // ne zelimo da enkodujemo blanko znak
            if (lines[i][j] == ' ') continue;

            char encoded_char = lines[i][j] + shift;

            // ako smo stigli do z treba da se vratimo unazad
            // oduzimanjem Z dobijamo koliki nam je shift onda za +A idemo na to slovo i -1 zato sto krecemo od 0;
            if (encoded_char > 'Z') encoded_char = encoded_char - 'Z' + 'A' - 1;
            lines[i][j] = encoded_char;
        }
    }
}

void print_lines(char **lines) {
    for (int i = 0; lines[i] != NULL; i++) {
        printf("%s%s", lines[i],
            (lines[i+1] != NULL)?"\n":"");
    }
}

void free_lines(char **lines) {
    for (int i = 0; lines[i] != NULL; i++) {
        free(lines[i]);
    }
    free(lines);
}

int main() {
    int shift;
    scanf("%d\n", &shift);

    char **lines = read_lines();
    encode(lines, shift);
    print_lines(lines);

    free_lines(lines);
    return 0;
}