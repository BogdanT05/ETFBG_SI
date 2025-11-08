#include "queue.h"

// Kopirajuci konstruktor, pravi duboku kopiju
// Na nove memoriske lokacije smesta podatke
// Bezbedno mozemo da unistimo pocetni red
Queue::Queue(Queue &queue) {
    this->len = queue.len;
    this->capacity = queue.capacity;
    this->first = queue.first;
    this->last = queue.last;

    this->queue = new int[queue.capacity];
    for (int i = 0; i < capacity; i++) {
        this->queue[i] = queue.queue[i];
    }
}

// Pomerajuci konstruktor pravi plitku kopiju
// koristi se za kopiranje podataka koji su blizu
// kraja svog zivotnog veka
Queue::Queue(Queue&& queue) {
    this->capacity = queue.capacity;
    this->len = queue.len;
    this->first = queue.first;
    this->last = queue.last;
    this->queue = queue.queue;
    queue.queue = nullptr;
}

void Queue::push_data(int num) {
    this->len++;
    this->last++;
    this->queue[last] = num;
}

int Queue::pop_data() {
    this->len--;
    this->first++;
    return this->queue[first];
}

bool Queue::is_empty() const{
    return len == 0;
}

bool Queue::is_full() const {
    return this->len == this->capacity;
}

// Prvi stvarni element se nalazi na poziciji ispred pokazivaca first
// moduo capacity se radi da bi postigli kruzni bafer
// odnosno podatke mozemo smestati i na pocetak niza
void Queue::write_queue() const {
    for (int i = 1; i <= this->len; i++) {
        cout << this->queue[(first+i) % capacity] << " ";
    }
    cout << endl;
}

void Queue::empty_queue() {
    this->len = 0;
    this->first = 0;
    this->last = 0;
}

