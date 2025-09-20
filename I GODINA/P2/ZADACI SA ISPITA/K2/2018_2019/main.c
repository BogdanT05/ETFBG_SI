#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char **load_map(int *rows) {
    scanf("%d ", rows);
    // memorija i pomocni brojaci
    char **map = malloc(*rows*sizeof(*map));
    char *line = NULL;
    int i = 0, j = 0, counter = 0;

    // vrtimo petlju dok ne unesemo sve parove
    while (counter < *rows) {
        char c = getchar();

        // ako smo uneli manje od dva elementa dodajemo u vrstu, necemo space
        if (i < 2 && c != ' ') {
            line = realloc(line, (i+1)*sizeof(*line));
            line[i] = c;
            i++;
        }

        // ako imamo dva elementa u vrsti resetujemo vrstu i povecavamo counter
        if (i == 2) {
            map[j] = line;
            j++;
            i = 0;
            line = NULL;
            counter++;
        }
    }

    return map;
}

int char_to_digit(char c, char **map, int rows) {
    int digit = 0;
    // penal nema sta objasnjavati :D
    for (int i = 0; i < rows; i++) {
        if (map[i][0] == c) {digit = map[i][1] - '0'; break;}
    }
    return digit;
}

int string_to_int(char *word, char **map, int rows) {
    int value_int = 0;
    int counter = 0;

    for (int j = strlen(word); j >= 0; j--) {
        value_int = value_int + char_to_digit(word[j], map, rows) * pow(10, counter-1);
        counter++;
    }

    return value_int;
}

char *read_line() {
    char *line = NULL;
    char c;
    int i = 0;

    if ((c = getchar()) == '\n') return "";
    ungetc(c, stdin);

    while (1) {
        c = getchar();
        if (c == '\n') break;
        line = realloc(line, (i+1)*sizeof(*line));
        line[i] = c;
        i++;
    }

    line[i] = '\0';
    return line;
}

void free_map(char **map, int rows) {
    for (int i = 0; i < rows; i++) {
        free(map[i]);
    }
    free(map);
}

int main() {
    int rows, i = 0;
    char **map = load_map(&rows);
    int value12 = 0, value3 = 0;

    while (i < 3) {
        char *word = read_line();

        if (i != 2) {
            value12 += string_to_int(word, map, rows);
        }else {
            value3 = string_to_int(word, map, rows);
        }

        free(word);
        word = NULL;
        i++;
    }

    if (value3 == value12) {
        printf("DA");
    }else {
        printf("NE");
    }

    free_map(map, rows);
    return 0;
}