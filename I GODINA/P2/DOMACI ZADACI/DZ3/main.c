
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reading_line() {
    char *line = NULL, c;
    int i = 0;

    // Unos jedne linije koda
    while ((c = getchar()) != '\n') {
        line = realloc(line, (i+1)*sizeof(*line)); // Za svako slovo pravimo memoriju, sporo ali stringovi nisu dugacki
        if (line == NULL) { // proveravamo alloc
            free(line);
            return NULL;
        }
        line[i] = c;
        i++;
    }
    if (line == NULL || strlen(line) == 0) return NULL; // ako je unet prazan red zavrsavamo unos casopisa

    // ako nismo zavrsili unos onda pravimo od svakog reda string
    line[i] = '\0';
    line[i-1] = '\n';
    return line;
}

int check_duplicates(char **text, char *str, int counter) {
    int i = 0;
    // prolazimo kroz niz stringova i proveravamo da li se u njemu vec nalazi odredjeni string
    for (;i < counter; i++) {
        if (strcmp(text[i], str) == 0) { // ako su stringovi isti strcmp vraca 0
            return 0;
        }
    }
    return 1;
}

void sort_by_name_and_age(char ***list, int counter) {
    int i,j;
    char **temp;
    // leksikografsko i numericko sortiranje po godinama
    // bubble sort
    for (i = 0; i < counter-1; i++) {
        for (j = i+1; j < counter; j++) {
            if (atoi(list[i][3]) > atoi(list[j][3])) { // atoi vraca int od stringa do prvog ne int znaka, prosto proveravamo koja godina je veca
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
            else if (atoi(list[i][3]) == atoi(list[j][3])) { // ako su godine iste potrebno je leksikografski sortirati
                if (strcmp(list[i][1], list[j][1]) > 0) { // strcmp > 0 ako je str1 leksikografski ispred str2, < 0 obrnuto
                    temp = list[i];
                    list[i] = list[j];
                    list[j] = temp;
                }
            }
        }
    }
}

char **formating_list(char **text, int counter, int *out_len) {
    char **formated_list = NULL;
    int i, j, cnt = 0;
    // Lista imena casopisa bez duplikata
    for (i = 0; i < counter; i++) {
        char *scratch = strdup(text[i]); // koristimo kopiju zato sto strtok menja originalni string
                                        // kada bi stavili samo text[i] izgubili bi podatke u koji se tu nalaze
        char *line = strtok(scratch, ","); // razdvajamo elementa na prvom zarezu
        j = 0;
        while  (j < 2) {
            line = strtok(NULL, ","); // uzimamo element posle drugog zareza, strtok pamti string koji je koristio
            j++;
        }
        if (check_duplicates(formated_list, line, cnt)) {
            formated_list = realloc(formated_list, (cnt+1)*sizeof(*formated_list)); // ako nije duplikat dodajemo ga u listu i pravimo prostor za taj elemenet
            formated_list[cnt] = strdup(line); // koristimo kopiju zato sto se line menja pa cemo pogresne elemente dodati
                                                // hocemo da zapamtimo tacno one elemente iz ove iteracije, u sledecoj bi ih izgubili
            cnt++;
        }
        free(scratch); // oslobadnjamo memoriju
    }

    // Sad treba za tu listu da proverimo koji su casopisi izasli u njoj
    int len = 0;
    char **formated_list_final = NULL;

    for (i = 0; i < cnt; i++) {
        char ***correct_elements = NULL; // lista matrica, tj lista listi stringova
                                        // koristimo da bi u nju stavili sve stringove  razdvojene po zarezu
        int x = 0;

        for (j = 0; j < counter; j++) {
            char *scratch = strdup(text[j]); // koristimo duplikat da ne promenimo originalni string
            char **line_el = malloc(4 * sizeof(*line_el)); // svaka podlista ce imati tacno 4 elementa (zadato u zadatku)
            int k = 0;
            char *tok = strtok(scratch, ","); // razdvajanje po prvom zarezu, i strtok pamti string
            while (k < 4) {
                line_el[k] = tok; // za svaki podstring koji napravimo dodajemo ga u novu listu
                tok = strtok(NULL, ","); // uzimamo string nakon sledeceg zareza
                k++;
            }

            if (strcmp(formated_list[i], line_el[2]) == 0) { // proveravamo da li je odgovarajuci casopis

                correct_elements = realloc(correct_elements, (x + 1) * sizeof(*correct_elements)); // ako jeste pravimo mesto za tacno tu listu stringova
                correct_elements[x] = malloc(4 * sizeof(*correct_elements[x])); // ta lista stringova ce imati tacno 4 stringa
                for (int e = 0; e < 4; e++) {
                    correct_elements[x][e] = strdup(line_el[e]); // smestamo svaki string na svoju poziciju
                                                                // koristimo strdup zato sto se line el menja a mi hocemo tacno ove podatke
                }
                x++;
            }

            free(line_el);   // oslobadjamo memoriju
            free(scratch);
        }

        sort_by_name_and_age(correct_elements, x);
        formated_list_final = realloc(formated_list_final, (len+1+x)*sizeof(*formated_list_final)); // pravimo konacnu listu koja ce imati
                                                                                // tacno onoliko mesta koliko treba da ispisemo
                                                                                // ime casopisa, radovi...
        formated_list_final[len++] = strdup(formated_list[i]); // stavljamo ime casopisa, kopija zato sto se menja
        for (int f = 0; f < x; f++) { // x duzina korektnih radova koje treba da dodamo
            formated_list_final[len++] = strdup(correct_elements[f][1]); // dodajemo redom samo imena radova objavljenih u tom casopisu
            // oslobadjamo memoriju za narednu iteraciju
            for (int g = 0; g < 4; g++) {
                free(correct_elements[f][g]);
            }
            free(correct_elements[f]);
        }
        free(correct_elements);
    }

    free(formated_list);
    *out_len = len; //  pokazivac na broj elemenata da bi znali koliko el da ispisemo na kraju
    return formated_list_final;
}

int check_doi(char **text, int counter){
    int i, doi;

    for (i = 0; i < counter; i++) {
        doi = atoi(*(text+i)+3); // uzimamo brojeve nakon 10.nnnn i proveravamo
        if (doi < 1000) return 1;
    }

    return 0;
}

int main(void) {
    char *text_line, **text = NULL, **formated_list = NULL;
    int counter = 0, i, len = 0;

    while (1) {
        text_line = reading_line();
        if (text_line == NULL) break; // ako je prazna linija
        text = realloc(text, (counter+1)*sizeof(*text)); // ako nije prazna linija pravimo prostor u memoriji

        if (text == NULL) { // ako je alokacije fejlovala oslobadjamo do tad zauzetu memoriju
            for (i = 0; i < counter+1;  i++) {
                free(text[i]);
            }
            free(text);
            printf("MEM_GRESKA");
            return 0;
        }
        // ako je sve korektno dodajemo liniju u text
        text[counter] = text_line;
        counter++;
    }

    if (check_doi(text, counter)) { // proveravamo doi ako nije korektno oslobadjamo memoriju i prekidamo program
        for (i = 0; i < counter; i++) {
            free(text[i]);
        }
        free(text);
        printf("GRESKA");
        return 0;
    }

    formated_list = formating_list(text, counter, &len);

    for (i = 0; i < len; i++) {
        printf("%s\n", formated_list[i]); // ispis i oslobajanje liste
        free(formated_list[i]);
    }
    free(formated_list);

    for (i = 0; i < counter; i++) { // oslobadjanje liste text
        free(text[i]);
    }

    free(text);
    return 0;
}