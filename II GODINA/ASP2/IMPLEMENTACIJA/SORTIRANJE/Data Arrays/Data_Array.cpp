#include "Data_Array.h"
#include <iostream>
#include <random>

int Data_Array::get_size() const {
    return array.size();
}

void Data_Array::generate_array(int capacity, int lower, int higher) {
    array.clear();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(lower, higher);

    for (int i = 0; i < capacity; i++) {
        array.push_back(dist(gen));
    }
}

void Data_Array::fill_array(int capacity) {
    int value;
    for (int k = 0; k < capacity; k++) {
        std::cout << "Unesi element: ";
        std::cin >> value;
        array.push_back(value);
    }
}

void Data_Array::swap(int i, int j) {
    std::swap(array[i], array[j]);
    for (int k = 0; k < observers.size(); k++) {
        observers[k]->on_swap(i, j);
    }
}

void Data_Array::set(int index, int value) {
    array[index] = value;
    for (int k = 0; k < observers.size(); k++) {
        observers[k]->on_set(index, value);
    }
}

bool Data_Array::compare(int i, int j) const {
    for (int k = 0; k < observers.size(); k++) {
        observers[k]->on_compare(i, j);
    }
    return array[i] > array[j];
}

void Data_Array::range(int l, int r) const {
    for (int k = 0; k < observers.size(); k++) {
        observers[k]->on_range(l, r);
    }
}

void Data_Array::add_observer(Observer *observer) {
    observers.push_back(observer);
}
