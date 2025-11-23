#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <deque>

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
    std::vector<Data> data;
    Node *root;
public:

    BinaryTree() : root(nullptr){}

    BinaryTree(const BinaryTree &tree) : root(nullptr) {
        data = tree.data;
        make_minial_tree();
    }

    BinaryTree(BinaryTree &&tree) noexcept {
        this->root = tree.root;
        this->data = std::move(tree.data);
        tree.root = nullptr;
    }

    ~BinaryTree() {
        // TODO: Destruktor iterativno
        if (root == nullptr) return;

        std::stack<Node*> stack;
        Node *current = root;
        Node *last_visited = nullptr;

        while (current != nullptr || !stack.empty()) {
            // idemo najlevlje moguce niz stablo i dodajemo na stek da mozemo da posetimo
            if (current != nullptr) {
                stack.push(current);
                current = current->left;
            }else {
                // ako cvor na vrhu steka ima desno podstablo i ako ga nismo posetili
                // prelazimo u desno podstabloi nastavljamo postupak pomeranja u levo
                // ne skidamo nista sa steka da bi mogli da posetimo pocetni cvor tj roditelja
                Node *peek = stack.top();
                if (peek->right != nullptr && peek->right != last_visited) {
                    current = peek->right;
                }
                // ako ne postoji desno dete ili smo ga vec posetili onda
                // posecujemo cvor tj roditelja i njega oznacavamo kao zadnjeg posecenog
                // skidamo ga sa steka i prelazimo na sledeci cvor
                else {
                    last_visited = peek;
                    stack.pop();
                    delete peek;
                }
            }
        }
        root = nullptr;
    }

    [[nodiscard]] bool check_root() const{return root == nullptr;}

    bool add_node(Node *node){
        // Pomocna funkcija
        if (root == nullptr) {
            root = node;
            return true;
        }
        Node *current = root;
        // Pamtimo kom cvoru treba da dodamo dete
        Node *previous = nullptr;
        while (current != nullptr) {
            // Ako nadjemo taj cvor znaci da ne mozemo da ga dodamo
            if (current->data.loyalty_points == node->data.loyalty_points) return false;
            previous = current;

            if (current->data.loyalty_points > node->data.loyalty_points) current = current->left;
            if (current->data.loyalty_points < node->data.loyalty_points) current = current->right;
        }

        // Dodajemo ga levo ili desno u odnosu na roditelja i menjamo pokazivac na roditelja
        if (previous != nullptr && previous->data.loyalty_points > node->data.loyalty_points) previous->left = node;
        if (previous != nullptr && previous->data.loyalty_points < node->data.loyalty_points) previous->right = node;
        node->parent = previous;
        return true;
    }

    bool delete_node(const Node *node) {
        // Pomocna funkcija
        if (root == nullptr) return false;
        Node *current = root;
        while (current != nullptr) {
            if (current->data.loyalty_points == node->data.loyalty_points) break;
            if (current->data.loyalty_points > node->data.loyalty_points) current = current->left;
            if (current->data.loyalty_points < node->data.loyalty_points) current = current->right;
        }

        auto child_swap = [this](const Node* current_, Node *child_){
            if (current_->parent == nullptr) root = child_;
            else if (current_->parent->left == current_) current_->parent->left = child_;
            else if (current_->parent->right == current_) current_->parent->right = child_;
            if (child_ != nullptr) child_->parent = current_->parent;
        };

        if (current == nullptr) return false; // Ako se cvor ne nalazi u stablu
        if (current->left == nullptr || current->right == nullptr) {
            Node *child = (current->left == nullptr)? current->right : current->left;
            child_swap(current, child);
            delete current;
            return true;
        }

        Node *successor = current->right;
        while (successor->left != nullptr) successor = successor->left;
        Node *successor_child = successor->right;

        if (successor->parent == current) current->right = successor_child;
        else successor->parent->left = successor_child;

        if (successor_child != nullptr) {
            successor_child->parent = successor->parent;
        }

        current->data = successor->data;
        delete successor;
        return true;
    }

    [[nodiscard]] int get_height() const{
        std::deque<Node*> queue;
        int height = -1; // pocetna visina ako je stablo prazno
        Node *sentinel = nullptr;
        if (root != nullptr) queue.push_back(root);
        else return height;

        queue.push_back(sentinel);
        while (!queue.empty()) {
            Node *current = queue.front();
            queue.pop_front();
            // Ako smo na nullptr onda smo obisli citav jedan nivo
            if (current == sentinel) {
                height++;
                if (queue.empty() == 0) break;
                queue.push_back(sentinel);
                continue;
            }
            // Cvorovi novog nivoa se uvek dodaju posle granicnika
            if (current->left != nullptr) queue.push_back(current->left);
            if (current->right != nullptr) queue.push_back(current->right);

        }
        return height;
    }

    bool read_data(std::istream& input) {
        std::string loyalty_points_str, name, surname, header;
        // Uzimamo prvu liniju tj header koji nam nije potreban
        std::getline(input, header);
        while (std::getline(input, loyalty_points_str, ',')) { // Prvo citamo do zareza da ucitamo poene
            // Pretvaramo poene u integer i citamo ostatak podataka
            if (loyalty_points_str == "END") break;
            int loyalty_points = std::stoi(loyalty_points_str);
            std::getline(input, name, ',');
            std::getline(input, surname);

            // Smestamo odg podatke u vektor podataka od koga pravimo stablo
            Data dat(loyalty_points, name, surname);
            this->data.push_back(dat);
        }

        return true;
    }

    [[nodiscard]] bool find_guest(int loyalty_points) const {
        Node *current = root;
        // Pomeramo se u levo ili desno podstablo u zavisnosti da li je kljuc koji trazimo
        // Veci ili manji od kljuca u tom cvoru.
        while (current != nullptr) {
            if (current->data.loyalty_points == loyalty_points) {
                std::cout << current->data.loyalty_points << " "
                << current->data.name << " " << current->data.surname;
                return true;
            }
            if (current->data.loyalty_points > loyalty_points) current = current->left;
            if (current->data.loyalty_points < loyalty_points) current = current->right;
        }

        return false;
    }

    void make_minial_tree() {
        struct StackNode {
            Node *next;
            int low;
            int high;

            StackNode(Node *node, int l, int h) : next(node), low(l), high(h){}
        };

        std::stack<StackNode>stack;
        int low = 0;
        int high = static_cast<int>(data.size()-1);
        int mid = (low + high)/2;

        root = new Node(data[mid].loyalty_points, data[mid].name, data[mid].surname);
        Node *current = root;
        stack.emplace(current, mid+1, high);

        high = mid-1;
        while (low <= high) {
            mid = (low + high)/2;
            auto *node_left = new Node(data[mid].loyalty_points, data[mid].name, data[mid].surname);

            current->left = node_left;
            node_left->parent = current;
            current = current->left;

            stack.emplace(current, mid+1, high);
            high = mid-1;
        }
        current->left = nullptr;

        while (!stack.empty()) {
            StackNode stack_node = stack.top();

            low = stack_node.low;
            high = stack_node.high;
            current = stack_node.next;

            stack.pop();
            if (low <= high) {

                mid = (low + high)/2;
                auto *node_right = new Node(data[mid].loyalty_points, data[mid].name, data[mid].surname);

                current->right = node_right;
                node_right->parent = current;
                current = current->right;
                stack.emplace(current, mid+1, high);

                high = mid - 1;
                while (low <= high) {
                    mid = (low + high)/2;
                    auto *node = new Node(data[mid].loyalty_points, data[mid].name, data[mid].surname);

                    current->left = node;
                    node->parent = current;
                    current = current->left;
                    stack.emplace(current, mid+1, high);

                    high = mid - 1;
                }
                current->left = nullptr;
            }
            else current->right = nullptr;
        }
    }

    bool increase_loyalty_points(int loyalty_points, int increase) {
        // TODO: Povecavanje poena, brisanje + dodavanje sa novim brojem poena
        Node *current = root;
        while (current != nullptr) {
            if (current->data.loyalty_points == loyalty_points) break;
            if (current->data.loyalty_points > loyalty_points) current = current->left;
            if (current->data.loyalty_points < loyalty_points) current = current->right;
        }

        if (current == nullptr) return false;
        auto node = new Node(loyalty_points + increase, current->data.name, current->data.surname);
        delete_node(current);
        if (!add_node(node)) return false; // Ako vec postoji sa tim poenima u stablu
        return true;
    }

    void print_tree() const {
        // TODO: Ispis, level order
        std::deque<Node*> queue;
        int initial_width = 120, current_width = 0, node_width = 0;
        if (root != nullptr) queue.push_back(root);
        while (!queue.empty()) {
            // initial width udaljenost izmedju pocetka i prvog cvora
            // current width udaljenost izmedju dva cvora
            // current_length broj cvorova u tom nivou
            // not_null broj ne nula elemenata
            if (initial_width < 2) break;
            int current_length = static_cast<int>(queue.size());
            initial_width = initial_width/2;
            current_width = initial_width * 2-1;
            int not_null = 0;

            for (int i = 0; i < current_length; i++) {
                // za svaki cvor u tom nivou proveravamo da li je prvi
                node_width = (i == 0)?initial_width:current_width+1;
                Node *node = queue.front();
                queue.pop_front();
                // vadimo cvor iz reda i ako je nullptr pisemo X i dodajemo dva nullptr da odrzimo broj elemenata u jednom nivou
                if (node == nullptr) {
                    std::cout << std::string(node_width+1, ' ') << "X";
                    queue.push_back(nullptr);
                    queue.push_back(nullptr);
                }
                else {
                    // ako je stvaran element ispisujemo ga i njegovu decu dodajemo u red nebitno ako us nullptr
                    std::cout << std::string(node_width-1, ' ') << node->data.loyalty_points;
                    queue.push_back(node->left);
                    queue.push_back(node->right);
                    // povecavamo not_null da potvrdimo da postoje realni elementi
                    not_null++;
                }
            }
            std::cout << std::endl;
            // ako je not_null == 0 znaci da je ispisan nivo sa svim 'X' tako da se u redu nalaze samo nullptr
            // to nam je znak da smo ispisali sve elemente iz stabla
            if (not_null == 0) break;
        }
    }

    void find_interval(int loyalty_points_min, int loyalty_points_max) const{
        // TODO: Naci interval na osnovu nekog obilaska
        Node *current = root;
        std::stack<Node*> stack;

        // Inorder obilazak, idemo levo i guramo na stek
        // Nakon toga prelazimo u desno podstablo i opet idemo najlevlje moguce
        while (true) {
            while (current != nullptr) {
                stack.push(current);
                current = current->left;
            }
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
                if (current->data.loyalty_points >= loyalty_points_min && current->data.loyalty_points <= loyalty_points_max)
                    std::cout << current->data.loyalty_points << " ";
                current = current->right;
            }
            else break;
        }
    }

    void inorder() const {
        Node *current = root;
        std::stack<Node*> stack;

        // Inorder obilazak, idemo levo i guramo na stek
        // Nakon toga prelazimo u desno podstablo i opet idemo najlevlje moguce
        while (true) {
            while (current != nullptr) {
                stack.push(current);
                current = current->left;
            }
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
                std::cout << current->data.loyalty_points << " ";
                current = current->right;
            }
            else break;
        }
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
    std::cout << " |   7. Povecanje poena                         |\n";
    std::cout << " |   0. Izlaz                                   |\n";
    std::cout << " |                                              |\n";
    std::cout << " ===============================================\n";
    std::cout << RESET;
}

int main() {
    auto *tree = new BinaryTree;
    std::string filename;
    int points, min, max, increase;

    while (true) {
        print_menu();

        int choice;
        std::cout << "Izaberite opciju: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                if (tree->check_root() == false) {
                    std::cout << "Tree already exist!";
                    break;
                }
                std::cout << "Unesite ime fajla: ";
                std::cin >> filename;
                std::ifstream file(filename);

                if (file.is_open() == false) {
                    std::cout << "File does not exist!";
                    break;
                }

                tree->read_data(file);
                tree->make_minial_tree();
                break;
            }
            case 2:
                if (tree->check_root() == false) {
                    break;
                }
                std::cout << "Unesite niz podataka (loyalty points, name, surname)(END, za izlaz sa zarezom) : \n";
                tree->read_data(std::cin);
                tree->make_minial_tree();
                break;
            case 3:
                if (tree->check_root()) {
                    std::cout << "Tree does not exist!";
                    break;
                }
                std::cout << "Unesite broj poena za pretragu: ";
                std::cin >> points;
                if (tree->find_guest(points) == false) std::cout << "Gost ne postoji u hotelu!\n";
                break;
            case 4:
                if (tree->check_root()) {
                    std::cout << "Tree does not exist!";
                    break;
                }
                std::cout << "Unesite donju i gornju granicu (min, max): ";
                std::cin >> min >> max;
                tree->find_interval(min, max);
                break;
            case 5:
                if (tree->check_root()) {
                    std::cout << "Tree does not exist!";
                    break;
                }
                tree->print_tree();
                break;
            case 6:
                if (tree->check_root()) {
                    std::cout << "Tree does not exist!";
                    break;
                }
                tree->inorder();
                break;
            case 7:
                if (tree->check_root()) {
                    std::cout << "Tree does not exist!";
                    break;
                }
                std::cout << "Unesite broj poena koji zelite da povecate i povecanje: ";
                std::cin >> points >> increase;
                tree->increase_loyalty_points(points, increase);
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
