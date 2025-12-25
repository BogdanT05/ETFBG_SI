#include "Tree234.h"

Tree234::Tree234() {
    root = nullptr;
}

Tree234::Tree234(const Tree234 &tree234) {
}

Tree234::Tree234(Tree234 &&tree234) noexcept {
    root = tree234.root;
    tree234.root = nullptr;
}

bool Tree234::insert_node(Process process) {
}

bool Tree234::delete_process() {
}

Process Tree234::find_process(int waiting_time, int execution_time) {
}

bool Tree234::read_tree(FILE *file) {
}

void Tree234::print_tree234(std::ostream &os) {
}

void Tree234::print_tree_red_black(std::ostream &os) {
}

Process Tree234::find_minimum() const {
}

Tree234::~Tree234() {
    root = nullptr;
}
