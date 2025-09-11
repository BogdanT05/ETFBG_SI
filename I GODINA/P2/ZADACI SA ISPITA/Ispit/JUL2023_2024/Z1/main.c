#include <stdio.h>
#include <stdlib.h>

int **read_data (int *num) {
    scanf("%d", num);
    int **data = calloc(*num, sizeof(*data)); // memorija za nizove

    for (int i = 0; i < *num; i++) {
        data[i] = calloc(*num, sizeof(*data[i])); // memorija za duzinu svakog niza
        for (int j = 0; j < *num; j++) {
            scanf("%d", &data[i][j]);
        }
    }

    return data;
}

void remove_city(int ***prices, int *num, int city) {
    int **cities = *prices;
    for (int i = city; i < *num-1; i++) { // pomeramo vrstu koju treba da obrisemo na zadnje mesto
        int *temp = cities[i+1];
        cities[i+1] = cities[i];
        cities[i] = temp;
    }

    free(cities[*num-1]); // oslobadjamo zadnje mesto u matrici, tj zadnji niz
    for (int i = 0; i < *num-1; i++) {
        for (int j = city; j < *num-1; j++) { // sada treba da obrisemo i kolonu u kojoj se nalazi grad koji treba da obrisemo
            int temp_city = cities[i][j+1];   // pomeramo elemente iz svake vrste na kraj i realociramo duzinu vrste
            cities[i][j+1] = cities[i][j];
            cities[i][j] = temp_city;
        }
        cities[i] = realloc(cities[i], (*num-1)*sizeof(*cities[i]));
    }

    *num = *num - 1; // smanjujemo dimenzija matrice
}

void print_best_price(int **prices, int num, int from_city, int to_city) {
    int best_flight;

    if (prices[from_city][to_city] != -1) {
        best_flight = prices[from_city][to_city]; // pretpostavljamo da je najbrzi put direktan let
    }else {
        best_flight = -1;
    }

    int id = -1;
    for (int i = 0; i < num; i++) {
        if (prices[from_city][i] != -1 && prices[i][to_city] != -1) { // nalazimo najmanju sumu standardnim algoritmom
            int sum = prices[from_city][i] + prices[i][to_city];      // from_city vrstu i to_city kolonu i obrnuto
            if (sum < best_flight || best_flight == -1){              // x x x x
                best_flight = sum;                                    // o x o o
                id = i;                                               // o x o o
            }                                                         // o x o o
        }                                                             // samo ove dve kolone (vrste) su nam bitne zato sto
                                                                      // samo one mogu da vode do zeljenog grada.
    }

    if (id == -1) printf("%d", best_flight);
    else printf("%d(%d)", best_flight, id);
}

void free_matrix(int **data, int *num) {
    for (int i = 0; i < *num; i++) {
        free(data[i]);
    }
    free(data);
}

int main(){
    int num_cities, from_city, to_city;
    int **data = read_data(&num_cities);

    scanf("%d %d", &from_city, &to_city);
    // remove city nam nije preterano bitna za unos tako da nju ovde samo zveknemo kako hocemo
    remove_city(&data, &num_cities, 3);
    print_best_price(data, num_cities, from_city, to_city);

    free_matrix(data, &num_cities);
    return 0;
}
