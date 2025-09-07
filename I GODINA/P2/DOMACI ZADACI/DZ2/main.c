#include <stdio.h>
#define MAX_ARRAY_SIZE 1000

int main() {
    int br_senzora, arr_senzori[MAX_ARRAY_SIZE];
    int kod, otkljucava, najveci_otkljucava = 0;
    int i;

    scanf("%d", &br_senzora);

    // Proveravamo granice
    if (br_senzora <= 0 || br_senzora > MAX_ARRAY_SIZE) {
        return 0;
    }

    for (i = 0; i < br_senzora; i++) {
        scanf("%d", &arr_senzori[i]);
    }

    for (i = 0; i < br_senzora; i++) {
        printf("%d%c", arr_senzori[i],
            (i != br_senzora-1)?' ':'\n'  // Ternarni operator, ako nismo na zadnjem elementu
                                          // razmak, ako jesmo prelazimo u novi red
        );
    }

    while (1) {
        scanf("%d", &kod);
        if (kod == 0) {  // Zavrsavamo kada je kod 0
            break;
        }

        otkljucava = 1;
        for (i = 0; i < br_senzora; i++) {
            if (!(kod & arr_senzori[i])) {  // Binarna operacija 'and', 1 & 1 => True
                                            // Sve ostalo False, ako vrati broj koji u
                                            // sebi sadrzi 1, negacijom ce biti false znaci ne otkljucava.
                otkljucava = 0;
                break;                      // Potrebno je da svaki el otkljucava tako da
                                            // cim naidjemo na neki koji ne prekidamo petlju
            }
        }

        if (otkljucava) {
            if (kod > najveci_otkljucava) najveci_otkljucava = kod; // Pronalazak najveceg koji otklucava
            printf("OTVARA\n");
        }else {
            printf("NE OTVARA\n");
        }
    }

    if (najveci_otkljucava) {
        printf("%d", najveci_otkljucava);
    }
    else {
        printf("%d", 0);
    }

    return 0;
}