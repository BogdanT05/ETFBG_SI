#include "Tree234.h"

void print_menu() {
    std::cout << "========================================\n";
    std::cout << "| 1. Kreiraj prazno stablo             |\n";
    std::cout << "| 2. Obrisi celo stablo                |\n";
    std::cout << "| 3. Ubaci novi proces                 |\n";
    std::cout << "| 4. Obrisi proces iz stabla           |\n";
    std::cout << "| 5. Pronadji proces                   |\n";
    std::cout << "| 6. Ucitaj procese iz datoteke        |\n";
    std::cout << "| 7. Ispisi jedan proces               |\n";
    std::cout << "| 8. Ispisi 2-3-4 stablo               |\n";
    std::cout << "| 9. Ispisi kao crveno-crno stablo     |\n";
    std::cout << "|10. Simulacija (jedan korak)          |\n";
    std::cout << "|11. Kompletna simulacija              |\n";
    std::cout << "| 0. Izlaz                             |\n";
    std::cout << "========================================\n";
    std::cout << "Izaberite opciju: ";
}

int main() {
    int choice;

    while (true) {
        print_menu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                // TODO: kreiraj prazno stablo
                break;
            case 2:
                // TODO: obrisi celo stablo
                break;
            case 3:
                // TODO: ubaci novi proces
                break;
            case 4:
                // TODO: obrisi proces iz stabla
                break;
            case 5:
                // TODO: pronadji proces
                break;
            case 6:
                // TODO: ucitaj procese iz datoteke
                break;
            case 7:
                // TODO: ispisi jedan proces
                break;
            case 8:
                // TODO: ispisi 2-3-4 stablo
                break;
            case 9:
                // TODO: ispisi kao crveno-crno stablo
                break;
            case 10:
                // TODO: simulacija jedan korak
                break;
            case 11:
                // TODO: kompletna simulacija
                break;
            case 0:
                return 0;
            default:
                break;
        }

        std::cout << "\n";
    }
}