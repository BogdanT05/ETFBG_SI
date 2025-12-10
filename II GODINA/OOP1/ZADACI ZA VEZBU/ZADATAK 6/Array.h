#ifndef ZADACI_ZA_VEZBU_ARRAY_H
#define ZADACI_ZA_VEZBU_ARRAY_H
#include "Complex.h"

class Iterator;

class Array {
private:
    int capacity;
    complex::Complex *data;

    void clear();
    void copy(const Array &array);
    void move(Array &array);

    friend void swap(Array &array_a, Array &array_b) noexcept;

public:
    explicit Array(int capacity = 5) : capacity(capacity), data(new complex::Complex[capacity]){}

    Array(const Array &array);
    Array(Array &&array) noexcept;

    int get_capacity() const {return capacity;}

    // Array& operator = (const Array &array);
    // Array& operator = (Array &&array) noexcept;
    Array& operator = (Array array); // Copy and swap idiom - Replacement for copy and move assignment

    complex::Complex& operator [] (int index);
    const complex::Complex& operator [] (int index) const;

    int operator () (const complex::Complex &complex) const;
    int operator () (const complex::Complex &complex, int high, int low) const;

    friend class Iterator;
    Iterator get_iterator();

    ~Array() {
        delete [] data;
        data = nullptr;
    }
};


#endif //ZADACI_ZA_VEZBU_ARRAY_H