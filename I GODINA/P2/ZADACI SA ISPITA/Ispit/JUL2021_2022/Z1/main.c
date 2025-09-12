#include <stdlib.h>
#include <stdio.h>

int **read_data(int *n) {
    scanf("%d", n);
    int **data = malloc(*n*sizeof(*data)); // broj vrsta u matrici
    for (int i = 0; i < *n; i++) {
        int j = 0;
        data[i] = NULL;
        while (1) {
            // za svaku vrstu unosimo brojeve dok ne naidjemo na prazan red
            // ovako omogucavamo razlicit broj elemenata u svakoj vrsti
            data[i] = realloc(data[i], (j+1)*sizeof(*data[i]));
            scanf("%d", &data[i][j]);
            if (getchar() == '\n') break;
            j++;
        }
    }
    return data;
}

int **filter_data(int **data, int *n) {
    int w = 0;
    for (int i = 0; i < *n; i++) {
        int player_1 = 0;
        int player_2 = 0;

        // Ako su oba igraca imala potez od najmanje 5 znaci treba da obrisemo tu vrstu
        for (int k = 1; k <= data[i][0]; k++) {
            if (k % 2 == 0 && data[i][k] >= 5) player_1 = 1;
            if (k % 2 == 1 && data[i][k] >= 5) player_2 = 1;
            if (player_1 && player_2) break;
        }

        if (player_1 && player_2) {
            free(data[i]);
        }else {
            // Ako nisu imali treba da sacuvamo tu vrstu tako da je prepisujemo na pocetak
            data[w] = data[i];
            w++;
        }
    }
    *n = w; // nova duzina
    int **tmp = realloc(data, (size_t)w * sizeof *data); // realociramo matricu da bi izgubili nepotrebne vrste
    if (tmp) data = tmp;
    return data;
}

void write_data(int **data, int n) {
    for (int i = 0; i < n; i++) {
        for (int k = 1; k <= data[i][0]; k++) {
            printf("%d%c",data[i][k], (k == data[i][0])?'\n':' ');
        }
    }
}

void free_data(int **data, int n) {
    for (int i = 0; i < n; i++) {
        free(data[i]);
    }
    free(data);
}

int main() {
    int n;
    int **data = read_data(&n);
    data = filter_data(data, &n);

    write_data(data, n);
    free_data(data, n);
    return 0;
}