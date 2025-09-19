#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_string() {
    char c;
    int i = 0;
    char *line = NULL;

    // ako je prazan red vracamo nista
    if ((c = getchar()) == '\n') return "";
    ungetc(c, stdin);

    while (1) {
        // skeniramo citav red do \n
        scanf("%c", &c);
        if (c == '\n') break;
        line = realloc(line, (i+2)*sizeof(*line));
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    return line;
}

char **read_strings() {
    char **strings = malloc(sizeof(*strings));
    int i = 0;

    // uz pomoc prethodne funkcije dodajemo dok ne procitamo prazan red
    while (1) {
        char *line = read_string();
        if (strcmp(line, "") == 0) break;

        strings = realloc(strings, (i+2)*sizeof(*strings));
        strings[i] = line;
        i++;
    }

    strings[i] = NULL;
    return strings;
}

void print_strings(char **strings) {
    for (int i = 0; strings[i] != NULL; i++) {
        printf("%s%s", strings[i],
            (strings[i+1] != NULL)?"\n":"");
    }
}

char **split(char **strings) {
    char **split = malloc(sizeof(*split));
    char *word = NULL;
    int i = 0;
    int j = 0;

    // treba reci da splitujemo po praznom prostoru i po kraju reci
    for (int k = 0; strings[k] != NULL; k++) {
        for (int z = 0; z < strlen(strings[k]); z++) {
            // ako je kraj ili blank treba da dodamo u novu listu listi
            if (strings[k][z] == ' '|| z+1 == strlen(strings[k])) {
                // ako je kraj reci ne zelimo da izgubimo taj karakter zadnji
                if (z+1 == strlen(strings[k])) {
                    word = realloc(word, (i+2)*sizeof(*word));
                    word[i] = strings[k][z];
                    i++;
                }
                // dodajemo i resetujemo brojac i word
                word[i] = '\0';
                i = 0;
                split = realloc(split, (j+2)*sizeof(*split));
                split[j] = strdup(word);
                free(word);
                word = NULL;
                j++;
            }else {
                // ako su slova dodajemo ih u word
                word = realloc(word, (i+2)*sizeof(*word));
                word[i] = strings[k][z];
                i++;
            }
        }
    }

    split[j] = NULL;
    return split;
}

void free_strings(char **strings) {
    for (int i = 0; strings[i] != NULL; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    char **strings = read_strings();
    char **result = split(strings);

    print_strings(result);

    free_strings(result);
    free_strings(strings);
    return 0;
}