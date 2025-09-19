#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line() {
    char c;
    int i = 0;
    char *line = NULL;
    // proveravamo da li je unos prazan ako jeste vracamo prazan string
    if ((c=getchar()) == '\n') return "";
    ungetc(c, stdin); // vracamo karakter da ga ne izgubimo

    while (1) {
        scanf("%c", &c);
        // provera da li smo do kraja reda stigli
        if (c == '\n') break;
        line = realloc(line,(i+2)*sizeof(*line));
        line[i] = c;
        i++;
    }

    line[i] = '\0';
    return line;
}

char **read_lines() {
    char **lines = malloc(sizeof(*lines));
    char *line;
    int i = 0;

    while (1) {
        line = read_line();
        if (strcmp(line, "") == 0) break;

        lines = realloc(lines, (i+2)*sizeof(*lines));
        lines[i] = line;
        i++;
    }

    lines[i] = NULL;
    return lines;
}

char *remove_extra_spaces (char *line) {
    int new = 0;
    // sa dva pokazivaca prolazimo kroz string i prepisujemo korektne elemente
    for (int i = 0; i < strlen(line); i++) {
        if (line[i] != ' ' || line[i+1] != ' ') {
            line[new] = line[i];
            new++;
        }
    }

    line[new] = '\0';
    return line;
}

void free_lines(char **lines) {
    int i = 0;
    for (; lines[i] != NULL; i++) {
        free(lines[i]);
    }
    free(lines);
}

int main(){
    char **lines = read_lines();
    // ovo komentarisano je za moodle, da ne prijavljuje memory leak
    for (int i = 0; lines[i] != NULL; i++) {
        //char *old = lines[i];
        lines[i] = remove_extra_spaces(lines[i]);
        //free(old);
        printf("%s%s", lines[i],
            (lines[i+1] != NULL)?"\n":"");
    }

    free_lines(lines);
    return 0;
}
