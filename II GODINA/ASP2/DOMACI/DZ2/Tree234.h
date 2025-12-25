#ifndef ETFBG_SI_TREE234_H
#define ETFBG_SI_TREE234_H
#include <iostream>
#include "Process.h"

class Tree234 {
private:
    struct Node {
        int num_of_keys;
        Process keys[3];
        Node* children[4]{};

        bool is_leaf;

        Node() : num_of_keys(0), is_leaf(true){
            for (int i = 0; i < 4; i++) children[i] = nullptr;
        }
    };

    Node *root;

public:
    Tree234();
    Tree234(const Tree234 &tree234);
    Tree234(Tree234 &&tree234) noexcept;

    [[nodiscard]] bool is_empty() const {return !root;}

    bool insert_node(Process process);
    bool delete_process();
    Process find_process(int waiting_time, int execution_time);

    bool read_tree(FILE *file);
    void print_tree234(std::ostream &os);
    void print_tree_red_black(std::ostream &os);

    [[nodiscard]] Process find_minimum() const;

    ~Tree234();
};


#endif