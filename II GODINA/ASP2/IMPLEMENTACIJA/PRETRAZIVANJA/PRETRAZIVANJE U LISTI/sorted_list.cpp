#include "sorted_list.h"

// Ovakva pretraga smanjuje broj pretraga ako element ne postoji u listi
int sorted_seq_search(int list[], int key, int length) {
    for (int i = 0; i < length; i++) {
        if (list[i] > key) break;
        if (list[i] == key) return i;
    }
    return -1; // Oznaka da element ne postoji u listi
}

int* sorted_seq_search_multiple(int list[], int keys[], int length_list, int length_keys) {
    int *matches = new int[length_keys]();
    int j;
    int i = j = 0;

    while (i < length_list && j < length_keys) {
        if (list[i] == keys[j]) {
            matches[j] = i;
            j++;
        }
        else if (list[i] > keys[j]) {
            j++;
        }
        i++;
    }

    return matches;
}

// Veoma efikasan nacin pretrage za uredjenje liste
// U svakom koraku odbacujemo polovinu mogucih kandidata
// Slozenost O(log n)
int binary_search(int list[], int key, int length) {
    int low = 0;
    int high = length-1;

    while (low <= high) {
        int mid = (low+high) / 2;

        if (list[mid] == key) return mid; // Uspesna pretraga, vraca poziciju
        if (list[mid] < key) low = mid+1;
        else high = mid-1;
    }

    return -1; // Neuspela pretraga
}

// Radi lakseg dodavanja elemenata u listu zauzimamo veci prostor nego sto nam je potrebno
// Formira se niz validnosti u kome 1 oznacava da taj element postoji a 0 da ne postoji
// Pa prilikom dodavanja novih elemenata imamo slobodan prostor za dodavanje a brisanje samo promenimo bit validnosti
// Slobodna mesta popunjavamo elementom koji je <= od prethodnog

int binary_search_extended(int elements[], int positions[], int key, int capacity) {
    int *list = new int[capacity]();
    int *bit_list = new int[capacity]();
    int fill = 0;
    // Na pozicije upisujemo odg elemente i pamtimo filler koji cemo pisati dok ne dodjemo
    // Do sledeceg validnog elementa
    for (int i = 0, j = 0; i < capacity; i++) {
        if (i == positions[j]) {
            bit_list[i] = 1;
            list[i] = elements[j];
            fill = elements[j];
            j++;
        }else {
            list[i] = fill;
            bit_list[i] = 0;
        }
    }

    int result = binary_search(list, key, capacity);
    // Ako generalno kljuc ne postoji result je -1, a ako se ne nalazi na validnoj poziciji onda to proveramo
    if (bit_list[result] == 0 && result != -1) result = -1; // Ta pozicija ne postoji u listi

    delete [] list;
    delete [] bit_list;

    return result;
}

// Ako ne znamo velicinu liste mozemo sami odredjivati interval
// Moze cak biti brze od obicne binarne pretrage ako znamo da se kljuc
// Nalazi oko pocetka liste i lista ima puno elemenata,
// Uslov za to je i < sqrt(n), gde je i duzina intervala
int binary_search_unknown_size(int list[], int key) {
    int low = 0;
    int high = 1;
    if (list[0] == key) return 0; // Ako se nalazi na prvoj poziciji trazeni el

    while (list[high] < key) { // pretpostavljamo da je niz dovoljno veliki, tj da list[high] nece izaci iz opsega
        low = high;
        high *= 2;
    }

    while (low <= high) {
        int mid = (low+high) / 2;

        if (list[mid] == key) return mid; // Uspesna pretraga, vraca poziciju
        if (list[mid] < key) low = mid+1;
        else high = mid-1;
    }

    return -1;
}

// Slican kao binarna pretraga ali se koristi drugaciji metod za izracunavanje sredine
// Koristi se kada su vrednosti elemenata jednako raspodeljenje, npr stranice knjige
// 112 stranu knjige necemo traziti od polovine nego od 1/5 knjige pa do 112
int interpolation_search(int list[], int key, int length) {
    int low = 0;
    int high = length-1;

    while (low <= high) {
        int mid = low + (high - low)*(key - list[low])/(list[high] - list[low]); // dobija se iz geometrije
        if (list[mid] == key) return mid; // uspesna pretraga
        if (list[mid] < key) low = mid+1;
        else high = mid-1;
    }

    return -1; // neuspesna pretraga
}

// Vremenska slozenost i odgovarajucoj listi je O(log (log n))
// Brza od binarne ali zahteva vise podataka o listi i rizicna je
// Ako nisu zadovoljeni uslovi slozenost raste do O(n)
