#include <iostream>

class BinaryTree {
private:
    struct Data {
        int loyalty_points;
        std::string name, surname;

        Data() : loyalty_points(-1){}
        Data(int loyalty_points, std::string name, std::string surname) :
        loyalty_points(loyalty_points), name(std::move(name)), surname(std::move(surname)){}
    };

    struct Node {
        Node *left;
        Node *right;
        Node *parent;
        Data data;

        Node() : left(nullptr), right(nullptr),
        parent(nullptr), data(Data()){}

        Node(int loyalty_points, std::string name, std::string surname) : left(nullptr),
        right(nullptr), parent(nullptr), data(Data(loyalty_points, std::move(name), std::move(surname))){}

        Node(int loyalty_points, std::string name, std::string surname, Node *left, Node *right, Node *parent) : left(left),
        right(right), parent(parent), data(Data(loyalty_points, std::move(name), std::move(surname))){}

    };
    Data *data;
    Node *root;
public:

    BinaryTree() : root(nullptr){}

    BinaryTree(BinaryTree &tree) {

    }

    BinaryTree(BinaryTree &&tree) noexcept {
        this->root = tree.root;
        this->data = tree.data;
        tree.root = nullptr;
        tree.data = nullptr;
    }

    ~BinaryTree() {
        // TODO: Destruktor iterativno
        delete [] data;
    }

    bool check_root() const{return root == nullptr;}

    bool add_node(Node *node) {
        // Pomocna funkcija
    }

    bool delete_node(Node *node) {
        // Pomocna funkcija
    }

    static Data* read_data() {
        // TODO: Citanje iz fajla i sa stdin
    }

    void find_guest(int loyalty_points) const {
        // TODO: Binarna pretraga u stablu
    }

    void make_minial_tree() {

    }

    bool increase_loyalty_points(int increase) {
        // TODO: Povecavanje poena, brisanje + dodavanje sa novim brojem poena
    }

    void print_tree() const {
        // TODO: Ispis, level order
    }

    void find_interval(int loyalty_points_min, int loyalty_points_max) const{
        // TODO: Naci interval na osnovu nekog obilaska
    }

    void inorder(Node *node) const {

    }

    void postorder(Node *node) const {

    }

};

void print_menu() {
    const std::string BLUE  = "\033[34m";
    const std::string RESET = "\033[0m";

    std::cout << BLUE;
    std::cout << " ===============================================\n";
    std::cout << " |                                              |\n";
    std::cout << " |   1. Unos iz fajla                           |\n";
    std::cout << " |   2. Unos sa standardnog ulaza               |\n";
    std::cout << " |   3. Pretraga stabla po poenima              |\n";
    std::cout << " |   4. Pretraga stabla u intervalu             |\n";
    std::cout << " |   5. Ispis stabla                            |\n";
    std::cout << " |   6. Ispis stabla po inorder                 |\n";
    std::cout << " |   7. Ispis stabla po postorder               |\n";
    std::cout << " |   0. Izlaz                                   |\n";
    std::cout << " |                                              |\n";
    std::cout << " ===============================================\n";
    std::cout << RESET;
}

int main() {
    auto *tree = new BinaryTree;

    while (true) {
        print_menu();

        int choice;
        std::cout << "Izaberite opciju: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                // TODO: Unos iz fajla

                if (BinaryTree::read_data() == nullptr) {
                    std::cout << "File does not exist!";
                    delete tree;
                    return 1;
                }
                tree->make_minial_tree();
                break;
            case 2:
                // TODO: Unos sa standardnog ulaza
                break;
            case 3:
                // TODO: Pretraga stabla po poenima
                if (tree->check_root()) {
                    std::cout << "Tree does not exist!";
                    delete tree;
                    return 2;
                }
                break;
            case 4:
                // TODO: Pretraga stabla u intervalu
                if (tree->check_root()) {
                    std::cout << "Tree does not exist!";
                    delete tree;
                    return 2;
                }
                break;
            case 5:
                // TODO: Ispis stabla
                if (tree->check_root()) {
                    std::cout << "Tree does not exist!";
                    delete tree;
                    return 2;
                }
                break;
            case 6:
                // TODO: Ispis stabla po inorder
                if (tree->check_root()) {
                    std::cout << "Tree does not exist!";
                    delete tree;
                    return 2;
                }
                break;
            case 7:
                // TODO: Ispis stabla po postorder
                if (tree->check_root()) {
                    std::cout << "Tree does not exist!";
                    delete tree;
                    return 2;
                }
                break;
            case 0:
                delete tree;
                return 0;
            default:
                std::cout << "Nepoznata opcija, pokusajte ponovo!\n";
                break;
        }

        std::cout << std::endl;
    }
}
