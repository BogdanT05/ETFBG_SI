#include "Tree234.h"

#include <deque>
#include <fstream>
#include <queue>
#include <stack>

std::ostream& operator << (std::ostream &os, const Tree234 *tree) {
    tree->print_tree234(os);
    tree->convert_234_to_rb(os);
    return os;
}

Tree234::Tree234() {
    root = nullptr;
}

// Pomocna funkcija za insert u postojeci cvor
void Tree234::insert_key(Node* node, Process* key, Node* rightChild) {
    int i = node->num_of_keys - 1;

    // Trazimo odg mesto na koje treba da ubacimo proces
    while (i >= 0 && *node->keys[i] > *key) {
        node->keys[i + 1] = node->keys[i];
        if (!node->is_leaf)
            node->children[i + 2] = node->children[i + 1];
        i--;
    }

    node->keys[i + 1] = key;

    // Ako nismo u listu moramo da pomerimo i dete, da bi odrzali strukturu 234 stabla
    if (!node->is_leaf)
        node->children[i + 2] = rightChild;

    node->num_of_keys++;
}

// Funkcija koja odrzava balans u citavom stablu prilikom umetanja u stablo
void Tree234::fix_overflow(Node* node) {
    while (node && node->num_of_keys == 4) { // Poziv samo kada neki cvor ima 4 kljuca, tj tada je overflow

        Process* middle = node->keys[1]; // Sredisnji kljuc koji ide gore u roditelja
        Node* right = new Node();
        right->is_leaf = node->is_leaf; // Pravimo novi cvor koji ce da ima isti oblik tj bice list zato sto dodajemo u list pa on postaje list

        // U taj novi cvor stavljamo 2 najveca iz cvora koji preliva
        right->keys[0] = node->keys[2];
        right->keys[1] = node->keys[3];
        right->num_of_keys = 2;

        // Prenosimo i decu u novi cvor
        right->children[0] = node->children[2];
        right->children[1] = node->children[3];
        right->children[2] = node->children[4];

        // Dodajemo roditeljski pokazivac za decu
        for (int i = 0; i < 3; i++)
            if (right->children[i]) right->children[i]->parent = right;

        // Levi tj stari cvor ostaje sa samo jednim (najmanjim kljucem tj najmanjim)
        node->num_of_keys = 1;
        node->keys[1] = node->keys[2] = node->keys[3] = nullptr;
        node->children[2] = node->children[3] = node->children[4] = nullptr;

        if (node->parent == nullptr) { // Ako cepamo koren moramo da napravimo novi koren i promenimo pokazivac
            Node* new_root = new Node();

            new_root->is_leaf = false;
            new_root->keys[0] = middle;

            new_root->children[0] = node;
            new_root->children[1] = right;
            new_root->num_of_keys = 1;

            node->parent = new_root;
            right->parent = new_root;
            root = new_root;
            return;
        }

        // Ako ne cepamo rut sredisnji kljuc ubacujemo u roditelja i njega po porebi ponovo prelamamo
        Node* parent = node->parent;
        insert_key(parent, middle, right);
        right->parent = parent;

        node = parent;
    }
}

// Balansira stablo kada u cvoru ostane 0 cvorova
void Tree234::fix_underflow(Node* node) {
    while (node && node->num_of_keys == 0) { // Petlja ako treba da sabijamo na vise nivoa

        if (node == root) { // Ako treba da sabijemo koren
            Node* old = root;
            root = root->children[0]; // Koren postaje sin jedan od dva preostala sina

            if (root) {
                root->parent = nullptr;
                root->is_leaf = (root->children[0] == nullptr); // Ako je koren ostao sam onda je list
            }

            delete old;
            return;
        }

        Node* parent = node->parent;
        int index = 0;
        while (parent->children[index] != node) index++; // Pronalazimo indeks na kom se nalazi cvor

        // Uzimamo levog i desnog brata ako nismo na pocetku ili kraju cvora
        Node* left  = (index > 0) ? parent->children[index - 1] : nullptr;
        Node* right = (index < parent->num_of_keys) ? parent->children[index + 1] : nullptr;

        // Leva pozajmica, samo ako levi brat ima vise od jednog kljuca
        // Roditelj ide u prazni, brat ide u roditelja, a deca se pomeraju
        if (left && left->num_of_keys > 1) {

            for (int i = node->num_of_keys; i >= 0; i--)
                node->children[i + 1] = node->children[i];

            node->keys[0] = parent->keys[index - 1];
            node->num_of_keys = 1;

            parent->keys[index - 1] = left->keys[left->num_of_keys - 1];
            left->num_of_keys--;

            if (!left->is_leaf) {
                node->children[0] = left->children[left->num_of_keys + 1];
                left->children[left->num_of_keys + 1] = nullptr;
                node->children[0]->parent = node;
                node->is_leaf = false;
            }
            return;
        }

        // Desna pozajmica, isto kao i leva samo na drugu stranu od desnog brata
        if (right && right->num_of_keys > 1) {

            node->keys[0] = parent->keys[index];
            node->num_of_keys = 1;

            parent->keys[index] = right->keys[0];

            for (int i = 0; i < right->num_of_keys - 1; i++)
                right->keys[i] = right->keys[i + 1];
            right->num_of_keys--;

            if (!right->is_leaf) {
                node->children[1] = right->children[0];
                for (int i = 0; i <= right->num_of_keys; i++)
                    right->children[i] = right->children[i + 1];

                node->children[1]->parent = node;
                node->is_leaf = false;
            }
            return;
        }

        // levo spajanje, ako ni jedan brat ne moze da pozajmi i ako levi brat postoji
        // Roditelj se spusta u levog, deca se prebacuju i cvor se brise.
        if (left) {
            int base = left->num_of_keys;

            // Spustamo roditelja
            left->keys[left->num_of_keys++] = parent->keys[index - 1];

            for (int i = 0; i < node->num_of_keys; i++)
                left->keys[left->num_of_keys++] = node->keys[i];

            // Pomeramo decu
            if (!node->is_leaf) {
                for (int i = 0; i <= node->num_of_keys; i++) {
                    left->children[base + 1 + i] = node->children[i];
                    if (left->children[base + 1 + i])
                        left->children[base + 1 + i]->parent = left;
                }
            }

            // Preuzima njegov status
            left->is_leaf = node->is_leaf;

            delete node;

            // Pravimo prostor u roditelju za umetanje kljuceva i dece
            for (int i = index - 1; i < parent->num_of_keys - 1; i++)
                parent->keys[i] = parent->keys[i + 1];

            for (int i = index; i < parent->num_of_keys; i++)
                parent->children[i] = parent->children[i + 1];

            parent->num_of_keys--;
            parent->children[parent->num_of_keys+1] = nullptr;

            node = parent;
        }

        // Desna spajanje isto kao i levo sa malim izmenama.
        else {
            int base = node->num_of_keys;

            node->keys[node->num_of_keys++] = parent->keys[index];

            for (int i = 0; i < right->num_of_keys; i++)
                node->keys[node->num_of_keys++] = right->keys[i];

            if (!right->is_leaf) {
                for (int i = 0; i <= right->num_of_keys; i++) {
                    node->children[base + 1 + i] = right->children[i];
                    if (node->children[base + 1 + i])
                        node->children[base + 1 + i]->parent = node;
                }
            }

            node->is_leaf = right->is_leaf;

            delete right;

            for (int i = index; i < parent->num_of_keys - 1; i++)
                parent->keys[i] = parent->keys[i + 1];

            for (int i = index + 1; i < parent->num_of_keys; i++)
                parent->children[i] = parent->children[i + 1];

            parent->num_of_keys--;
            parent->children[parent->num_of_keys + 1] = nullptr;

            node = parent;
        }
    }
}

// Vadimo najmanji proces, tj prvi u najlevljem cvoru
Process * Tree234::extract_min() {
    if (!root) return nullptr;

    // Spusamo se levo dok ne nadjemo odg proces
    Node* current = root;
    while (!current->is_leaf)
        current = current->children[0];

    Process* found = current->keys[0];

    // vadimo ga napolje iz cvora tj sabijamo cvor
    for (int i = 0; i < current->num_of_keys - 1; i++)
        current->keys[i] = current->keys[i + 1];
    current->num_of_keys--;

    fix_underflow(current);
    return found;
}

// Pretraga koja nam vraca tacnu poziciju nekog cvora i procesa u njemu koji hocemo da obrisemo
bool Tree234::find_node(Process *process, Node *&delete_node, int &delete_index) const {
    Node* current = root;
    while (current) {
        int i = 0;
        while (i < current->num_of_keys && *current->keys[i] < *process) i++;
        if (i < current->num_of_keys && current->keys[i] == process) { // Ako smo uspesno nasli u tom listu prekdiamo pretragu i vracamo
            delete_node = current;                                     // Indeks u cvoru i cvor koji smo nasli
            delete_index = i;
            return true;
        }
        current = current->children[i]; // Nastavljamo sa spustanjem niz stablo
    }
    return false;
}

// Brise tacno zadati proces iz stabla, nebitna pozicija
void Tree234::delete_process(Process* process) {
    Node* node;
    int index;
    if (!find_node(process, node, index)) return; // Prvo pretraga da li taj proces uopste postoji u stablu

    if (!node->is_leaf) { // Ako ne brisemo u listu drugacija situacija, tj trazimo sledbenika po inorderu.
        Node* successor = node->children[index + 1];
        while (!successor->is_leaf) successor = successor->children[0];
        node->keys[index] = successor->keys[0]; // Menjamo sa sledbenikom
        node = successor;
        index = 0;
    }

    // Izbacujemo iz lista i popravljamo underflow ako ima
    for (int i = index; i < node->num_of_keys - 1; i++)
        node->keys[i] = node->keys[i + 1];
    node->num_of_keys--;

    fix_underflow(node);
}

void Tree234::insert_node(Process* p) {
    // Ako ubacujemo u root
    if (!root) {
        root = new Node();
        root->keys[0] = p;
        root->num_of_keys = 1;
        return;
    }

    Node* current = root;

    // Silazimio prvo do odogovarajuceg liste u koji treba da ubacimo process.
    while (!current->is_leaf) {
        int i = 0;
        while (i < current->num_of_keys && *p > *current->keys[i]) i++;
        current = current->children[i];
    }

    // Ubacujemo u list
    insert_key(current, p, nullptr);

    // Popravljamo ako ima overflow
    fix_overflow(current);
}

// Pretraga po vremenu cekanja i izvrsavanja
Process *Tree234::find_process(int waiting_time, int execution_time) const {
    if (!root) return nullptr;

    // Privremeni proces koji nam pomaze pri pretrazi
    Process key("", 0, 0, waiting_time, execution_time);
    Node* current = root;

    while (current) {
        int i = 0;

        while (i < current->num_of_keys && *current->keys[i] < key)
            i++;

        if (i < current->num_of_keys &&
            current->keys[i]->get_waiting_time() == waiting_time &&
            current->keys[i]->get_execution_time() == execution_time) // Ako su svi uslovi zadovoljeni vracamo uspesnu pretragu
            return current->keys[i];

        current = current->children[i];
    }

    return nullptr;
}

void Tree234::update(int delta) { // Svima povecavamo waiting time, a oni koji predju max_wait njih izbacimo pa ubacimo
    if (!root) return;

    std::vector<Process*> list; // Pomocna lista u kojoj pamitmo kome treba da povecamo
                                // Stablo ne diramo dok obilazimo nego tek posle da ne bi pokvarili strukturu

    // Implementacija iterativnog inorder obilaska, imamo 3 faze
    // 1. Idemo u levo dete 2. Obradjujemo kljuceve, 3. izlazak iz cvora
    struct Frame { Node* n; int i; int phase; };
    std::stack<Frame> stack;
    stack.push({root, 0, 0});

    while (!stack.empty()) {
        auto& frame = stack.top();
        Node* node = frame.n;

        if (frame.phase == 0) {
            frame.phase = 1;
            frame.i = 0;
            if (node->children[0])
                stack.push({node->children[0], 0, 0});
        }
        else if (frame.phase == 1) {
            if (frame.i < node->num_of_keys) {
                list.push_back(node->keys[frame.i]);
                frame.i++;
                if (node->children[frame.i])
                    stack.push({node->children[frame.i], 0, 0});
            } else {
                frame.phase = 2;
            }
        }
        else stack.pop();
    }

    // Nakon sto smo zapamtili, svima uvecamo vreme
    for (Process* p : list)
        p->waiting_time += delta;

    for (Process* p : list) {
        // Ko je presao njega izbacimo, auziriramo vreme i izbacimo pa vratimio
        if (p->waiting_time >= p->maximum_waiting_time) {
            delete_process(p);
            p->waiting_time -= p->maximum_waiting_time;
            insert_node(p);
        }
    }
}

// Ispis sadrzaja jednog cvora
void Tree234::write_node(const Node *node, std::ostream &os) {
    os << "[";
    for (int i = 0; i < node->num_of_keys; i++) {
        os << node->keys[i]->get_name() << (i != node->num_of_keys-1? "|" : "");
    }
    os << "]";
}

// Citanje iz datoteke
bool Tree234::read_tree(std::ifstream &file) {
    std::string name;
    int time_to_complete, max_waiting_time;

    while (file >> name >> time_to_complete >> max_waiting_time) {
        auto *process = new Process(name, time_to_complete, max_waiting_time, 0, 0);
        std::cout << "UCITAN: " << name << " " << time_to_complete << " " << max_waiting_time << "\n";
        insert_node(process);
    }

    return true;
}

// Ispis uz pomoc BFS obilaska
void Tree234::print_tree234(std::ostream& os) const {
    if (!root) return;

    std::queue<Node*> q;
    q.push(root);

    int indent = 90;      // pocetni razmak
    int gap = 42;         // razmak izmedju cvorova

    indent -= gap / 2;

    while (!q.empty()) {
        unsigned n = q.size();

        if (q.front() == root) os << std::string(indent-24, ' ');
        else os << std::string(indent, ' ');

        for (int i = 0; i < n; i++) {
            Node* node = q.front(); q.pop();

            write_node(node, os);
            os << std::string(gap, ' ');

            // Ubacujemo svu decu koju treba da obidjemo
            for (int k = 0; k <= node->num_of_keys; k++)
                if (node->children[k])
                    q.push(node->children[k]);
        }
        os << "\n";

        // Namestamo brojeve da izgleda okej :)
        indent /= 2;
        if (indent < 1) indent = 1;
        gap /= 2;
        if (gap < 2) gap = 2;
    }
}

// Isti ispis kao i sa prethodnog domaceg za binarno stablo
void Tree234::print_red_black_binary(RBNode* rootRB, std::ostream &os) {
    std::queue<RBNode*> queue;
    int initial_width = 120, current_width = 0, node_width = 0;
    if (rootRB != nullptr) queue.push(rootRB);

    while (!queue.empty()) {
        if (initial_width < 2) break;
        int current_length = static_cast<int>(queue.size());

        initial_width = initial_width/2;
        current_width = initial_width * 2-1;
        int not_null = 0;

        for (int i = 0; i < current_length; i++) {
            node_width = (i == 0)?initial_width:current_width+1;
            RBNode *node = queue.front();
            queue.pop();

            if (node == nullptr) {
                os << std::string(node_width+1, ' ') << "X";
                queue.push(nullptr);
                queue.push(nullptr);
            }
            else {
                os << std::string(node_width-1, ' ') << (node->red ? "R:" : "B:") + node->key->get_name();
                queue.push(node->left);
                queue.push(node->right);
                not_null++;
            }
        }
        os << std::endl;
        if (not_null == 0) break;
    }
}

// Transformacija iz 234 u binarno tj crveno crno stablo
// Pretvara 234 cvor u jednu kombinaciju od 3 binarna cvora
void Tree234::convert_234_to_rb(std::ostream &os) const {
    if (!root) return;

    // Lambda funkcija koja uzima jedan 234 node
    // U zavisnosti od broja kljuceva pravi odgovarajuce rb podstablo
    auto make_rb = [](Node* node) -> RBNode* {
        if (!node) return nullptr;
        if (node->num_of_keys == 1) return new RBNode(node->keys[0], false);

        if (node->num_of_keys == 2) {
            auto* r = new RBNode(node->keys[1], false);
            r->left = new RBNode(node->keys[0], true);
            return r;
        }

        auto* r = new RBNode(node->keys[1], false);
        r->left  = new RBNode(node->keys[0], true);
        r->right = new RBNode(node->keys[2], true);
        return r;
    };

    RBNode* rootRB = make_rb(root); // Prvo pravimo koren sa njegovom decom

    std::queue<std::pair<Node*, RBNode*>> q;
    q.emplace(root, rootRB);

    while (!q.empty()) {
        auto [n234, rb] = q.front(); q.pop();
        if (n234->is_leaf) continue;

        // Ako 234 cvor nije list on moze da ima 2 3 4 dece i u zavisnoti od toga u stek guramo svu decu koju on ima
        // I od njih pravimo odgovarajuca rb podstabla i spajamo ih

        if (n234->num_of_keys == 1) {
            rb->left = make_rb(n234->children[0]);
            rb->right = make_rb(n234->children[1]);

            if (rb->left) q.emplace(n234->children[0], rb->left);
            if (rb->right) q.emplace(n234->children[1], rb->right);
        }
        else if (n234->num_of_keys == 2) {
            rb->left->left = make_rb(n234->children[0]);
            rb->left->right = make_rb(n234->children[1]);
            rb->right = make_rb(n234->children[2]);

            if (rb->left->left) q.emplace(n234->children[0], rb->left->left);
            if (rb->left->right) q.emplace(n234->children[1], rb->left->right);
            if (rb->right) q.emplace(n234->children[2], rb->right);
        }
        else {
            rb->left->left = make_rb(n234->children[0]);
            rb->left->right = make_rb(n234->children[1]);
            rb->right->left = make_rb(n234->children[2]);
            rb->right->right = make_rb(n234->children[3]);

            if (rb->left->left) q.emplace(n234->children[0], rb->left->left);
            if (rb->left->right) q.emplace(n234->children[1], rb->left->right);
            if (rb->right->left) q.emplace(n234->children[2], rb->right->left);
            if (rb->right->right) q.emplace(n234->children[3], rb->right->right);
        }
    }

    print_red_black_binary(rootRB, os); // Ispis na kraju
}

void Tree234::inorder_iterative() const {
    if (!root) return;

    struct Frame {
        Node* n;
        int i;
        int phase;
    };

    std::stack<Frame> stack;
    stack.push({root, 0, 0});

    while (!stack.empty()) {
        Frame& frame = stack.top();
        Node* node = frame.n;

        // 3 faze koje nam omogucvajaju da znamo da li smo zavrsili sve operacije sa cvorom
        // Ili treba jos nesto da radimo, na pocetku samo push i pamtimo da sledeci put kada dodjemo
        // Treba da uradimo nesto sa tim cvorom, zato menjamo fazu

        if (frame.phase == 0) {
            frame.phase = 1;
            frame.i = 0;
            if (node->children[0])
                stack.push({node->children[0], 0, 0});
        }
        else if (frame.phase == 1) {
            // Kada je faza 1 sve procese iz jednog cvora obilazimo i pamtimo dokle smo stigli sa obilak
            if (frame.i < node->num_of_keys) {
                std::cout << "[";
                std::cout << node->keys[frame.i]->get_name() <<", "<< node->keys[frame.i]->waiting_time
                << ", " <<node->keys[frame.i]->execution_time;
                std::cout << "]";
                frame.i++;
                if (node->children[frame.i])
                    stack.push({node->children[frame.i], 0, 0});
            } else {
                // Oznaka da smo obisli cvor i nastavljamo dalje
                frame.phase = 2;
            }
        }
        else {
            // Ako smo u fazi 2 popujemo is steka, zavrsili smo svu obradu nad tim dvorom
            stack.pop();
        }
    }
}

// Nalazimo najmanji u stablu kao prvi proces u najlevljem cvoru
Process* Tree234::find_minimum() const {
    if (root == nullptr) return nullptr;
    Node *current = root;

    while (!current->is_leaf) {
        current = current->children[0];
    }

    return current->keys[0];
}

// Destruktor redom dodaje cvorove u stablo i brise ih.
Tree234::~Tree234() {
    if (!root) return;

    std::stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* n = st.top();
        st.pop();

        if (!n->is_leaf) {
            for (int i = 0; i <= n->num_of_keys; i++) {
                if (n->children[i])
                    st.push(n->children[i]);
            }
        }

        delete n;
    }

    root = nullptr;
}
