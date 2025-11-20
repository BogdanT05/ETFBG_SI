
#ifndef PRETRAZIVANJE_U_STABLU_AVL_TREE_H
#define PRETRAZIVANJE_U_STABLU_AVL_TREE_H
#include "binary_tree.h"

class Avl_tree : public Binary_tree{
public:
    Avl_tree() : root(nullptr){}
    struct Node: Binary_tree::Node {
        int balance;
        Node *left;
        Node *right;
        Node(int data, int key, int balance) : Binary_tree::Node(data, key),
        balance(balance), left(nullptr), right(nullptr){}
    };

    bool add_node(int key, int data) override;
    static void rotate_left(Node *node);
    static void rotate_right(Node *node);

private:
    Node *root;
};


#endif //PRETRAZIVANJE_U_STABLU_AVL_TREE_H