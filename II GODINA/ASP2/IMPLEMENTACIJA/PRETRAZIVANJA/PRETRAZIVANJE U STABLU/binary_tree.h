//
// Created by bgdnt on 11/11/2025.
//

#ifndef PRETRAZIVANJE_U_LISTI_BINARY_TREE_H
#define PRETRAZIVANJE_U_LISTI_BINARY_TREE_H


class Binary_tree {
public:
    struct Node {
        int data;
        int key;
        Node *left;
        Node *right;

        Node() : data(0), key(0), left(nullptr), right(nullptr){}
        Node(int data, int key) : data(data), key(key), left(nullptr), right(nullptr){};
        explicit Node(int data, int key, Node *left, Node *right) {
            this->data = data;
            this->key = key;
            this->left = left;
            this->right = right;
        }

    };

    Binary_tree();
    Binary_tree(const Binary_tree &tree);
    Binary_tree(Binary_tree &&tree) noexcept;

    virtual ~Binary_tree();

    void write_tree() const;
    virtual bool add_node(int key, int data);
    virtual bool delete_node(int key);
    Node* bst_search(int key) const;
    void inorder() const;
    void preorder() const;
    void postorder() const;
    void level_order() const;

    Node* find_predecessor(int key) const;
    Node* find_successor(int key) const;
    Node* find_max() const;
    Node* find_min() const;

    int get_height() const;
    int get_width() const;

private:
    Node *root;
protected:
    static void destroy(const Node *node);
    static Node* clone(const Node *node);

    static auto pop_queue(const int &capacity, int &first, int &last, int &length, Binary_tree::Node *queue[capacity]);
    static auto push_queue(const int &capacity, int &first, int &last, int &length, Binary_tree::Node *queue[capacity]);

    static auto pop_stack(Binary_tree::Node *stack[256], int &stack_pointer);
    static auto push_stack(Binary_tree::Node *stack[256], int &stack_pointer);
};


#endif //PRETRAZIVANJE_U_LISTI_BINARY_TREE_H