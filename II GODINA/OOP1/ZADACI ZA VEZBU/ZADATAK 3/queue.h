#ifndef ZADACI_ZA_VEZBU_QUEUE_H
#define ZADACI_ZA_VEZBU_QUEUE_H
#include <iostream>
using namespace std;

class Queue{
private:
    int capacity, first, last, len;
    int *queue;
public:
    Queue(int cap) {
        this->capacity = cap;
        this->first = 0;
        this->last = 0;
        this->len = 0;
        this->queue = new int[capacity];
    }

    Queue(Queue& queue);
    Queue(Queue&& queue);

    void push_data(int num);
    int pop_data();
    bool is_empty() const;
    bool is_full() const;

    void write_queue() const;
    void empty_queue();

    ~Queue(){
        delete [] queue;
    }
};


#endif //ZADACI_ZA_VEZBU_QUEUE_H