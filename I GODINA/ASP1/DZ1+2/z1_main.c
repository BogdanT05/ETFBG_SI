#include <stdio.h>
#include "func.h"

void print_menu() {
    printf("\n====================================\n");
    printf("                MENI                \n");
    printf("====================================\n");
    printf("a. Kreiraj ulancanu listu\n");
    printf("b. Unisti ulancanu listu\n");
    printf("c. Ispisi ulancanu listu\n");
    printf("d. Umetni element na zadatu poziciju\n");
    printf("e. Obrisi element sa zadatom vrednoscu\n");
    printf("f. Pretrazi listu po zadatoj vrednosti\n");
    printf("g. Izlaz\n");
    printf("------------------------------------\n");
    printf("Izaberi opciju i pritisni ENTER: ");
}

int main(void) {
    char user_input;
    print_menu();
    Node *list = NULL;
    while (1) {
        int position, del_value, sub_menu_input, value;
        scanf("%c", &user_input);
        if (user_input == 'g'){
            free_list(list);
            break;
        }
        switch (user_input) {
            case 'a':
                printf("Unesite elemente liste(q da zavrsite unos): ");
                Node *list = form_list();
                break;
            case 'b':
                if (list != NULL) {
                    free_list(list);
                    list = NULL;
                }else {
                    perror("LISTA NE POSTOJI\n");
                }
                break;
            case 'c':
                if (list != NULL) {
                    print_list(list);
                }else {
                    perror("LISTA NE POSTOJI\n");
                }
                break;
            case 'd':
                if (list != NULL) {
                    printf("Unesite poziciji: ");
                    scanf("%d", &position);
                    list = insert_on_position(list, position);
                }else {
                    perror("LISTA NE POSTOJI\n");
                }
                break;
            case 'e':
                if (list != NULL) {
                    printf("Unesite vrednost koju zelite da obrisete: ");
                    scanf("%d", &del_value);
                    list = remove_nodes(list, del_value);
                }else {
                    perror("LISTA NE POSTOJI\n");
                }
                break;
            case 'f':
                if (list != NULL) {
                    printf("\n================= PODMENI: PRETRAGA LISTE =================\n");
                    printf("1. Prvo pojavljivanje vrednosti\n");
                    printf("2. Poslednje pojavljivanje vrednosti\n");
                    printf("3. Broj pojavljivanja vrednosti\n");
                    printf("0. Nazad u glavni meni\n");
                    printf("-----------------------------------------------------------\n");
                    printf("Izaberi opciju i pritisni ENTER: ");
                    scanf("%d", &sub_menu_input);

                    if (sub_menu_input == 0) break;
                    printf("Unesite vrednost za pretrazivanje: ");
                    scanf("%d", &value);

                    switch (sub_menu_input) {
                        case 1:
                            search_first(list, value);
                            break;
                        case 2:
                            search_last(list, value);
                            break;
                        case 3:
                            search_all(list, value);
                            break;
                        default:
                            break;
                    }
                }else {
                    perror("LISTA NE POSTOJI\n");
                }
                break;
            default:
                continue;
        }
        print_menu();
    }
}