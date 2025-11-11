#ifndef STARI_ROKOVI_LINKED_LIST_H
#define STARI_ROKOVI_LINKED_LIST_H

class Linked_list {
private:
    struct Node {
        int key;
        int content;
        Node *next;

        Node(int key = -1, int content = 0, Node* next = nullptr) {
            this->key = key;
            this->content = content;
            this->next = next;
        }
    };
    Node *head;
    Node *last;
public:
    Linked_list();
    Linked_list(const Linked_list &list);
    Linked_list(Linked_list &&list) noexcept;
    ~Linked_list();

    void add_element(int key, int content);
    void write_list() const;
    void delete_last();
    int sequential_search(int key) const;
    int sequential_search_limiter(int key);
    int move_to_front_seq_search(int key);
    int transposition_seq_search(int key) const;
};


#endif //_LINKED_LIST_H