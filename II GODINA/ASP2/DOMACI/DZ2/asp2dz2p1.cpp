#include <fstream>

#include "src/Scheduler.h"
#include "src/Tree234.h"

void print_menu() {
    std::cout << "========================================\n";
    std::cout << "| 1. Ubaci novi proces                 |\n";
    std::cout << "| 2. Obrisi proces iz stabla           |\n";
    std::cout << "| 3. Pronadji proces                   |\n";
    std::cout << "| 4. Ucitaj procese iz datoteke        |\n";
    std::cout << "| 5. Ispisi stablo kao 234 i RB        |\n";
    std::cout << "| 6. Simulacija (jedan korak)          |\n";
    std::cout << "| 7. Kompletna simulacija              |\n";
    std::cout << "| 0. Izlaz                             |\n";
    std::cout << "========================================\n";
    std::cout << "Izaberite opciju: ";
}

int main() {
    int choice;
    auto* tree = new Tree234;
    Scheduler scheduler(tree);

    std::ofstream output;
    output.open("result.txt");

    if (!output.is_open()) {
        std::cout << "Greska prilikom otvaranja!\n";
        return 1;
    }

    while (true) {
        print_menu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string n;
                int ttc, mwt;
                std::cout << "Unesi ime, vreme potrebno za izvrsavnja i maks vreme cekanja (A 299 340): ";
                std::cin >> n >> ttc >> mwt;

                auto* process = new Process(n, ttc, mwt, 0, 0);
                tree->insert_node(process);
                std::cout << "USPESNO DODAN PROCES.";
                break;
            }
            case 2: {
                int ttc, mwt;
                std::cout << "Unesi TTC i MWT za brisanje: ";
                std::cin >> ttc >> mwt;

                tree->delete_process(tree->find_process(ttc, mwt));
                std::cout << "USPESNO OBRISAN";
                break;
            }
            case 3: {
                int wt, et;
                std::cout << "Unesi WT i ET za pretragu: ";
                std::cin >> wt >> et;

                Process* p = tree->find_process(wt, et);

                if (!p) {
                    std::cout << "Proces sa tim WT i ET ne postoji!\n";
                } else {
                    std::cout << "Nadjen proces: " << p->get_name() << "\n";
                }
                break;
            }
            case 4:{
                std::string filename;
                std::cout << "Unesi ime datoteke: ";
                std::cin >> filename;

                std::ifstream file;
                file.open(filename);

                if (!file.is_open()) {
                    std::cout << "GRESKA PRILIKOM OTVARANJA FAJLA";
                    break;
                }

                tree->read_tree(file);
                file.close();
                std::cout << "Procesi uspesno ucitani";
                break;
            }
            case 5:
                tree->inorder_iterative();
                std::cout << "\n";
                std::cout << tree;
                break;
            case 6:
                scheduler.step(output);
                break;
            case 7:
                scheduler.run(output);
                break;
            case 0:
                output.close();
                return 0;
            default:
                break;
        }

        std::cout << "\n";
    }

}