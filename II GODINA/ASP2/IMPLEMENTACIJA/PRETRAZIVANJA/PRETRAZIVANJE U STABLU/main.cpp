#include <iostream>
#include "binary_tree.h"

void print_menu() {
    std::cout <<
    "+------------------------------------------------+------------------------------------------------+\n"
    "|  1. Dodaj cvor u stablo                         |  9.  Nadji sledbenika cvora                   |\n"
    "|  2. Obrisi cvor iz stabla                       | 10.  Nadji maksimum u stablu                  |\n"
    "|  3. Ispisi stablo                               | 11.  Nadji minimum u stablu                   |\n"
    "|  4. Inorder obilazak                            | 12.  Nadji visinu stabla                      |\n"
    "|  5. Preorder obilazak                           | 13.  Nadji sirinu stabla                      |\n"
    "|  6. Postorder obilazak                          | 14.  Pronadji cvor u stablu                   |\n"
    "|  7. Level order obilazak                        | 15.  Kopiraj stablo                           |\n"
    "|  8. Nadji prethodnika cvora                     |  0.  Izlaz                                    |\n"
    "+------------------------------------------------+------------------------------------------------+\n";

}

int main() {
    auto *tree = new Binary_tree;
    int choice;

    print_menu();
    while (true) {
        std::cout << "Izaberite opciju: ";
        std::cin >> choice;

        Binary_tree::Node *node;
        switch (choice) {
            default:
                break;
            case 0:
                exit(0);
            case 1:
                int new_key, new_data;
                std::cout << "Unesite kljuc i podatak: ";
                std::cin >> new_key >> new_data;
                tree->add_node(new_key, new_data);
                break;
            case 2:
                int delete_key;
                std::cout << "Unesite kljuc koji zelite da obrisete: ";
                std::cin >> delete_key;

                if (tree->delete_node(delete_key)) std::cout << "Uspesno obrisano! \n";
                else std::cout << "Cvor ne postoji u stablu! \n";
                break;
            case 3:
                tree->write_tree();
                break;
            case 4:
                tree->inorder();
                break;
            case 5:
                tree->preorder();
                break;
            case 6:
                tree->postorder();
                break;
            case 7:
                tree->level_order();
                break;
            case 8:
                int predecessor;
                std::cout << "Unesite kljuc cijeg prethodnika trazite: ";
                std::cin >> predecessor;
                node = tree->find_predecessor(predecessor);
                if (node != nullptr) std::cout << "Prethonik je cvor sa kljucem: " << node->key << std::endl;
                else std::cout << "Cvor nema prethodnika (Najmanji cvor u stablu) \n";
                break;
            case 9:
                int successor;
                std::cout << "Unesite kljuc cijeg sledbenika trazite: ";
                std::cin >> successor;
                node = tree->find_successor(successor);
                if (node != nullptr) std::cout << "Sledbenik je cvor sa kljucem: " << node->key << std::endl;
                else std::cout << "Cvor nema sledbenika (Najveci cvor u stablu) \n";
                break;
            case 10:
                node = tree->find_max();
                if (node != nullptr) std::cout << "Maksimum je cvor sa kljucem: " << node->key << std::endl;
                else std::cout << "Stablo je prazno! \n";
                break;
            case 11:
                node = tree->find_min();
                if (node != nullptr) std::cout << "Minimun je cvor sa kljucem: " << node->key << std::endl;
                else std::cout << "Stablo je prazno! \n";
                break;
            case 12:
                std::cout << "Visina stable je: " << tree->get_height();
                break;
            case 13:
                std::cout << "Sirina stable je: " << tree->get_width();
                break;
            case 14:
                int search_node;
                std::cout << "Unesi kljuc cvora za pretragu: ";
                std::cin >> search_node;
                node = tree->bst_search(search_node);
                if (node != nullptr) std::cout << "Cvor je pronadjen: " << node->data << std::endl;
                else std::cout << "Cvor ne postoji u stablu! \n";
                break;
            case 15:
                auto *copy_tree = new Binary_tree(*tree);
                copy_tree->write_tree();
                std::cout << "Uspesno kopiranje! \n";
                break;

        }
        std::cout << std::endl;
    }
}