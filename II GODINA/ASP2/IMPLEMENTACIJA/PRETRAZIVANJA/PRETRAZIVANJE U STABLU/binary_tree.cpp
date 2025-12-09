#include "binary_tree.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

auto Binary_tree::pop_stack(Node **stack, int &stack_pointer) {
    auto pop = [stack, &stack_pointer]()->Node* {
        if (stack_pointer == 0) return nullptr;
        Node *node = stack[--stack_pointer];
        return node;
    };
    return pop;
}

auto Binary_tree::push_stack(Node **stack, int &stack_pointer) {
    auto push = [stack, &stack_pointer](Node *node) {
        if (stack_pointer == 256) throw std::overflow_error("stack full");
        stack[stack_pointer++] = node;
    };
    return push;
}

auto Binary_tree::pop_queue(const int &capacity, int &first, int &last, int &length, Node **queue) {
    auto pop = [&]() -> Node* {
        if (length == 0) throw std::out_of_range("Red je prazan!");
        length--;
        Node* node = queue[first];
        first = (first + 1) % capacity;
        return node;
    };
    return pop;
}

auto Binary_tree::push_queue(const int &capacity, int &first, int &last, int &length, Node **queue){
    auto push = [&](Node *node) {
        if (length == capacity) throw std::out_of_range("Red je pun!");
        length++;
        queue[last] = node;
        last = (last + 1) % capacity;
    };
    return push;
}


Binary_tree::Binary_tree() {
    root = nullptr;
}

Binary_tree::Binary_tree(const Binary_tree &tree) {
    // Rekurzivno kloniramo svaki cvor
    root = clone(tree.root);
}

Binary_tree::Node* Binary_tree::clone(const Node *node) {
    Node* new_node = nullptr;
    if (node != nullptr) {
        // Dok ne dodjemo do nullptr cvora rekurzivno kopiramo sve cvorove
        Node* left_node = clone(node->left);
        Node* right_node = clone(node->right);
        // Kada krene unazad da se zavrsava rekurzija svi cvorovi ce medjusobno pokazivati na svoju decu
        new_node = new Node(node->data, node->key,
            left_node, right_node);
    }
    return new_node;
}

Binary_tree::Binary_tree(Binary_tree &&tree) noexcept{
    root = tree.root;
    tree.root = nullptr;
}

Binary_tree::~Binary_tree() {
    // Rekurzivno oslobadjamo memoriju
    destroy(root);
    root = nullptr;
}

void Binary_tree::destroy(const Node *node) {
    // Ako je nullptr ne brisemo u suprotnom idemo u dubinu dok ne dodjemo do cvore bez deteta
    if (node == nullptr) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

void Binary_tree::write_tree() const  {
    int capacity = 257;
    int first = 0;
    int last = 0;
    int length = 0;
    Node *queue[capacity];

    auto pop = pop_queue(capacity, first, last, length, queue);
    auto push = push_queue(capacity, first, last, length, queue);

    // Ispis (stackoverflow inspiracija :))
    // Uz pomoc level ordera i odg pocetnih parametara ispis
    int initial_width = static_cast<int>(pow(2, get_height() + 2)), current_width = 0, node_width = 0;
    if (root != nullptr) push(root);
    while (length != 0) {
        // initial width udaljenost izmedju pocetka i prvog cvora
        // current width udaljenost izmedju dva cvora
        // current_length broj cvorova u tom nivou
        // not_null broj ne nula elemenata
        int current_length = length;
        initial_width = initial_width/2;
        current_width = initial_width * 2-1;
        int not_null = 0;

        for (int i = 0; i < current_length; i++) {
            // za svaki cvor u tom nivou proveravamo da li je prvi
            node_width = (i == 0)?initial_width:current_width;
            Node *node = pop();
            // vadimo cvor iz reda i ako je nullptr pisemo X i dodajemo dva nullptr da odrzimo broj elemenata u jednom nivou
            if (node == nullptr) {
                std::cout << std::string(node_width, ' ') << "X";
                push(nullptr);
                push(nullptr);
            }
            else {
                // ako je stvaran element ispisujemo ga i njegovu decu dodajemo u red nebitno ako us nullptr
                std::cout << std::string(node_width, ' ') << node->key;
                push(node->left);
                push(node->right);
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

bool Binary_tree::add_node(int key, int data) {
    Node *node = new Node(data, key);

    if (root == nullptr) root = node;
    else{
        Node *previous = root;
        for (Node *current = root; current != nullptr;) {
            previous = current;
            if (current->key == key) {
                delete node;
                return false; // Element vec postoji u stablu
            }

            if (current->key < key) current = current->right; // Ako je kljuc veci od cvora idemo desno
            else current = current->left; // Ako je manji idemo levo
        }

        if (previous->key < key) previous->right = node;
        else previous->left = node;
    }
    return true;
}

bool Binary_tree::delete_node(int key) {
    if (root == nullptr) return false; // Ne brisemo ako je prazno stablo
    Node *current = root;
    Node *parent = nullptr;

    // Prvo pronalazimo cvor koji treba da obrisemo
    while (current != nullptr) {
        if (current->key == key) break;
        parent = current;
        if (current->key < key) current = current->right;
        if (current->key > key) current = current->left;
    }

    if (current == nullptr) return false; // Ne brisemo ako ne postoji cvor
    Node* left_child = current->left;
    Node* right_child = current->right;

    // 3 slucaja:
    // 1. 0 dece razmatramo kada je root onaj koji treba da obrisemo, kada je levo i desno dete
    // 2. 1 dete razmatramo kada se root brise, i kada je cvor koji se brise levo ili desno dete
    // 3. 2 dece ne brisemo bukvalno nego zamenimo podatke i brisemo samo cvor iz kog smo uzeli podatke
    // Provera da li brisemo levo ili desno dete da bi mogli korektno da promenimo pokazivac

    // Lambda funkcija koja iz spoljasnjeg opsega hvata pokazivac this da bi mogli da radimo sa root
    // auto oznacava da ce kompajler sam da odredi tip podatka
    auto child_swap = [this](Node* parent_, const Node* current_,Node *child_) {
        if (parent_ == nullptr) root = child_;
        else if (current_ == parent_->right) parent_->right = child_;
        else parent_->left = child_;
    };

    if (left_child == nullptr || right_child == nullptr) {
        // Ternarni operator da odredimo sta da prosledimo funkciji
        // Ako nema levo dete znaci da treba da prespojimo desno dete i obrnuto
        Node *child = (left_child == nullptr)? right_child:left_child;
        child_swap(parent, current, child);
        delete current;
        return true;
    }

    // Kada brisemo cvor sa dva deteta pronalazimo sledbenik, tj min u desnom podstablu
    // Pamtimo roditelja sledbenika da mozemo da promenimo pokazivac
    // Sledbenik sigurno nema levo dete, da ima ne bi bio sledbenik
    // Moze da ima samo desno podstablo tako da moramo da pazimo da to korektno prespojimo
    Node *successor = current->right;
    Node *succ_parent = current;

    while (successor->left != nullptr) {
        succ_parent = successor;
        successor = successor->left;
    }

    // Kada nadjemo sledbenika pazimo da li treba levo ili desno da ga spojimo
    // Kada je sledenik istovremeno i sin objekta kog treba da obrisemo moramo da ga prespojimo u desno
    // U suprotnom levo, zato sto je najlevlji biti sledbenik
    if (succ_parent == current) succ_parent->right = successor->right;
    else succ_parent->left = successor->right;

    // Kopiramo podatke
    current->key = successor->key;
    current->data = successor->data;

    delete successor;
    return true;
}

Binary_tree::Node* Binary_tree::bst_search(int key) const{
    Node *current = root;
    while (current != nullptr) {
        if (current->key == key) return current; // Uspesna pretraga
        if (current->key < key) current = current->right;
        else current = current->left;
    }
    return nullptr; // Neuspela pretraga vracamo nullptr
}

void Binary_tree::inorder() const {
    Node* stack[256];
    int stack_pointer = 0;

    auto pop = pop_stack(stack, stack_pointer);
    auto push = push_stack(stack, stack_pointer);

    Node *current = root;
    // inorder obilazak levo koren desno
    // idemo skroz levo i stavljamo cvorove sa
    // desnim podstablom na stek da znamo da se vratimo na njih i da posetimo i desno podstablo
    while (true) {
        while (current != nullptr) {
            push(current);
            current = current->left;
        }
        if (stack_pointer != 0) {
            // kada skidamo sa steka ujedno ih i posetimo i prelazimo u desno podstablo koje
            // obilazimo na isti nacin
            current = pop();
            std::cout << "[" << current->key << ", " << current->data << "]";
            current = current->right;
        }else break;
    }
}

void Binary_tree::preorder() const {
    // preorder koren levo desno
    Node* stack[256];
    int stack_pointer = 0;

    auto pop = pop_stack(stack, stack_pointer);
    auto push = push_stack(stack, stack_pointer);

    if (root != nullptr) push(root);

    while (stack_pointer != 0) {
        // stavljamo elemente na stek i odmah ih posecujemo, ako postoji desno
        // podstablo stavljamo ga na stek da ga kasnije posetimo i idemo u levo podstablo
        Node *current = pop();
        while (current != nullptr) {
            std::cout << "[" << current->key << ", " << current->data << "]";
            if (current->right != nullptr) push(current->right);
            current = current->left;
        }
    }
}

void Binary_tree::postorder() const {
    // postorder levo desno koren
    int stack_pointer = 0;
    Node* stack[256];

    auto pop = pop_stack(stack, stack_pointer);
    auto push = push_stack(stack, stack_pointer);

    Node *current = root;
    Node *last_visited = nullptr;
    // last viisted nam daje informacije o zadnjem elementu koji smo posetili
    while (current != nullptr || stack_pointer != 0) {
        // idemo najlevlje moguce niz stablo i dodajemo na stek da mozemo da posetimo
        if (current != nullptr) {
            push(current);
            current = current->left;
        }else {
            // ako cvor na vrhu steka ima desno podstablo i ako ga nismo posetili
            // prelazimo u desno podstabloi nastavljamo postupak pomeranja u levo
            // ne skidamo nista sa steka da bi mogli da posetimo pocetni cvor tj roditelja
            Node *peek = stack[stack_pointer - 1];
            if (peek->right != nullptr && peek->right != last_visited) {
                current = peek->right;
            }
            // ako ne postoji desno dete ili smo ga vec posetili onda
            // posecujemo cvor tj roditelja i njega oznacavamo kao zadnjeg posecenog
            // skidamo ga sa steka i prelazimo na sledeci cvor
            else {
                std::cout << "[" << peek->key << ", " << peek->data << "]";
                last_visited = peek;
                pop();
            }
        }
    }
}

void Binary_tree::level_order() const {
    // level order obilazak po nivoima uz pomoc reda, sa leva na desno
    int capacity = 256;
    int first = 0;
    int last = 0;
    int length = 0;
    Node *queue[capacity];

    auto pop = pop_queue(capacity, first, last, length, queue);
    auto push = push_queue(capacity, first, last, length, queue);

    if (root != nullptr) push(root);
    // dodajemo elemente na stek ako nisu nullptr i tako ih obradjujemo
    // FIFO pristup
    while (length != 0) {
        Node *current = pop();
        if (current->left != nullptr) push(current->left);
        if (current->right != nullptr) push(current->right);
        std::cout << "[" << current->key << ", " << current->data << "]";
    }
}

// Pronalazak prethodnika takodje 2 slucaja
// 1) ako imamo levo podstablo onda je prethodnik najdesni cvor u levom podstablu
// 2) ako nemamo levo podstablo onda ce prethodnik biti cvor kod koga
// zadnji put skrecemo desno desno tj onaj cvor kome je trazeni cvor sledbenik
// pamtimo pokazivac na cvor poslednjeg skretanja desno
Binary_tree::Node* Binary_tree::find_predecessor(int key) const{
    Node *parent = nullptr;
    Node *current = root;

    // Trazimo cvor i pamtimo skretanje desno
    while (current != nullptr) {
        if (current->key == key) break;
        if (current->key < key) {
            parent = current;
            current = current->right;
        }
        else current = current->left;
    }

    if (current == nullptr) return nullptr; // Ne postoji kljuc

    // Ako imamo levo podstablo trazimo u njemu prethodnika inace vracamo skretanje desno
    if (current->left != nullptr) {
        current = current->left;
        while (current->right != nullptr) current = current->right;
        return current;
    }
    return parent;
}

// Da bi pronasli sledbenika moramo da razmotrimo dva slucaja:
// 1) Ako postoji desno podstablo tada ce sledbeniki biti min u desnom podstablu
// 2) Ako ne postoji desno podstablo tada ce sledbenik biti najmladji predak
// Kome je on levi potomak, tj cvor zadnji cvor kod koga smo otisli levo
Binary_tree::Node* Binary_tree::find_successor(int key) const{
    Node *parent = nullptr;
    Node *current = root;

    while (current != nullptr) {
        if (current->key == key) break; // Uspesna pretraga
        if (current->key < key) current = current->right;
        else {
            parent = current;
            current = current->left;
        }
    }

    if (current == nullptr) return nullptr; // Ako kljuc ne postoji

    if (current->right != nullptr) {
        current = current->right;
        while (current->left != nullptr) current = current->left;
        return current; // Minimum u desnom podstablu
    }
    return parent; // Ako nema desno podstablo najmladji predak ce da bude sledbenik
                   // Tj. zadnje skretanje levo u stablu. Ako ne postoji sledbenik i paretn ce biti nullptr
}

// Maksimum u stablu je najdesniji cvor
Binary_tree::Node* Binary_tree::find_max() const{
    Node *current = root;
    Node *previous = root;

    while (current != nullptr) {
        previous = current;
        current = current->right;
    }

    return previous;
}

Binary_tree::Node* Binary_tree::find_min() const{
    Node *current = root;
    Node *previous = nullptr;

    while (current != nullptr) {
        previous = current;
        current = current->left; // Cvor sa najmanjim kljucem se nalazi najlevlje u stablu
    }

    return previous; // Ako vrati nullptr stablo je prazno u suprotnom postoji min
}

// Visinu nalazimo iz level ordera i grancinog pokazivaca
// Nakon svakog obilaska dodajemo nullptr da bi znali kada da povecamo dubinu
int Binary_tree::get_height() const{
    int capacity = 256;
    int first = 0;
    int last = 0;
    int length = 0;
    Node *queue[capacity];

    auto pop = pop_queue(capacity, first, last, length, queue);
    auto push = push_queue(capacity, first, last, length, queue);

    int height = -1; // pocetna visina ako je stablo prazno
    Node *sentinel = nullptr;
    if (root != nullptr) push(root);
    else return height;

    push(sentinel);
    while (length != 0) {
        Node *current = pop();
        // Ako smo na nullptr onda smo obisli citav jedan nivo
        if (current == sentinel) {
            height++;
            if (length == 0) break;
            push(sentinel);
            continue;
        }
        // Cvorovi novog nivoa se uvek dodaju posle granicnika
        if (current->left != nullptr) push(current->left);
        if (current->right != nullptr) push(current->right);

    }
    return height;
}

// Sirina slicno kao i visina level order i pamcenje trenutne sirine
// i poredjenje sa do tada maks visinom
int Binary_tree::get_width() const {
    int capacity = 256;
    int first = 0;
    int last = 0;
    int length = 0;
    Node *queue[capacity];

    auto pop = pop_queue(capacity, first, last, length, queue);
    auto push = push_queue(capacity, first, last, length, queue);

    if (root != nullptr) push(root);
    else return 0;

    Node *sentinel = nullptr;
    push(sentinel);

    int max_width = 1;
    int width = 0;

    while (length != 0) {
        Node *current = pop();
        if (current == sentinel) {
            if (width > max_width) max_width = width;
            if (length == 0) break;
            push(sentinel);
            width = 0; // resetujemo sirinu za svaki nivo
            continue;
        }
        if (current->left != nullptr) {
            push(current->left);
            width++;
        }
        if (current->right != nullptr) {
            push(current->right);
            width++;
        }
    }
    return max_width;
}