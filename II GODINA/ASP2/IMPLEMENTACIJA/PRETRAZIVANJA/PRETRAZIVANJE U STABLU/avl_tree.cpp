#include "avl_tree.h"

void Avl_tree::rotate_left(Node *node) {
    Node *current = node->right;
    Node *temp = current->left;
    current->left = node;
    node->right = temp;
}

void Avl_tree::rotate_right(Node *node) {
    Node *current = node->left;
    Node *temp = current->right;
    current->right = node;
    node->left = temp;
}

bool Avl_tree::add_node(int key, int data) {
    Node *node = new Node(data, key, 0);
    if (root == nullptr) root = node;
    else {
        Node *parent, *critical, *parent_critical;
        Node *current = parent = critical = parent_critical =root;
        while (current != nullptr) {
            if (current->key == key) return false; // Cvor postoji vec
            if (current->balance != 0) {
                critical = current;
                parent_critical = current;
            }                                               // Cvorovi koji imaju balance 0 sigurno nece ispasti iz ravnoteze ako se doda jedan cvor
            parent = current;                                                // Samo nagnuti cvorovi mogu ispasti iz ravnoteze, tako pamtimo najdublji cvor koji je nagnut
            if (current->key < key) current = current->right;
            if (current->key > key) current = current->left;
        }

        if (parent->key < key) parent->right = node;
        if (parent->key > key) parent->left = node;

        if (critical->key < key) current = critical->right; // Cvor od kog je narusen balans
        if (critical->key > key) current = critical->left;

        Node *temp = current;
        while (current != nullptr && current != node) {
            if (current->key > key) {
                current->balance = 1;
                current = current->left;
            }
            else {
                current->balance = -1;
                current = current->right;
            }
        }

        int imbalance;
        if (critical->key > key) imbalance = 1;
        else imbalance = -1;

        if (critical->balance ==  0) {critical->balance = imbalance; return true;}
        if (critical->balance != imbalance) {critical->balance = 0; return true;}

        if (temp->balance == imbalance) {
            current = temp;
            if (imbalance == 1) rotate_right(critical);
            else rotate_left(critical);

            critical->balance = current->balance = 0;
        }
        else {
            if (imbalance == 1) {
                current = temp->right;
                rotate_left(temp);
                critical->left = current;
                rotate_right(critical);
            }
            else {
                current = temp->left;
                critical->right = current;
                rotate_right(temp);
                rotate_left(critical);
            }

            if (current->balance == 0) critical->balance = temp->balance = 0;
            else {
                if (current->balance == imbalance) {
                    critical->balance = -imbalance;
                    temp->balance = 0;
                }
                else {
                    critical->balance = 0;
                    temp->balance = imbalance;
                }
                current->balance = 0;
            }
        }
        if (critical == root) root = current;
        else {
            if (critical == parent_critical->right) parent_critical->right = current;
            else parent_critical->left = current;
        }
    }

    return true;
}

