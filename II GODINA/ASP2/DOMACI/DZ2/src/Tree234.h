#ifndef ETFBG_SI_TREE234_H
#define ETFBG_SI_TREE234_H
#include <iostream>

#include "Process.h"

class Tree234 {
private:
    friend class Process;

    struct Node {
        int num_of_keys;
        Process* keys[4]{};
        Node* children[5]{};

        Node* parent;
        bool is_leaf;

        Node() : num_of_keys(0), parent(nullptr),is_leaf(true) {
            for (int i = 0; i < 5; ++i) children[i] = nullptr;
            for (int i = 0; i < 4; i++) keys[i] = nullptr;
        }
    };

    struct RBNode {
        Process* key;
        bool red;
        RBNode* left;
        RBNode* right;

        RBNode(Process* process, bool red) : key(process), red(red), left(nullptr), right(nullptr){}
    };

    Node *root;

    static void print_red_black_binary(RBNode* rootRB, std::ostream &os);
    bool find_node(Process* process, Node*& delete_node, int& delete_index) const;

public:
    friend std::ostream& operator << (std::ostream &os, const Tree234* tree);
    void inorder_iterative() const;
    Tree234();

    [[nodiscard]] bool is_empty() const {return !root;}

    static void insert_key(Node *node, Process *key, Node *rightChild);
    void insert_node(Process* process);

    void fix_overflow(Node* x);
    void fix_underflow(Node* node);

    void delete_process(Process* process);
    [[nodiscard]] Process* find_minimum() const;
    Process* extract_min();

    [[nodiscard]] Process* find_process(int waiting_time, int execution_time) const;

    void update(int delta);

    static void write_node(const Node* node, std::ostream &os) ;
    bool read_tree(std::ifstream &file);
    void print_tree234(std::ostream &os) const;
    void convert_234_to_rb(std::ostream &os) const;

    ~Tree234();
};


#endif