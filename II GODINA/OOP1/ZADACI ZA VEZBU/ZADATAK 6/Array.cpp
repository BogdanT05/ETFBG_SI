#include "Array.h"

void swap(Array &array_a, Array &array_b) noexcept {
    std::swap(array_a.capacity, array_b.capacity);
    std::swap(array_a.data, array_b.data);
}


void Array::clear() {
    delete [] data;
    data = nullptr;
}

void Array::copy(const Array &array) {
    data = new complex::Complex[capacity = array.capacity];
    for (int i = 0; i < capacity; i++) {
        data[i] = array.data[i];
    }
}

void Array::move(Array &array) {
    this->capacity = array.capacity;
    this->data = array.data;

    array.data = nullptr;
}

// Copy constructor
Array::Array(const Array &array) {
    this->copy(array);
}

// Move constructor
Array::Array(Array &&array) noexcept {
    this->move(array);
}

// Copy assignment
// Array& Array::operator=(const Array &array) {
//     if (this != &array) {
//         this->clear();
//         this->copy(array);
//     }
//
//     Array tmp = array;
//     swap(*this, tmp);
//
//     return *this;
// }

// Move assignment
// Array& Array::operator = (Array &&array) noexcept {
//     if (this != &array) {
//         this->clear();
//         this->move(array);
//     }
//
//     swap(*this, array);
//
//     return *this;
// }

// Copy and swap idiom, replacement for separate move and copy assignment, shorter and more efficient
Array &Array::operator=(Array array) {
    swap(*this, array);
    return *this;
}

complex::Complex &Array::operator[](int index) {
    // (*this)[index] is calling non-const operator and that is creating infinite recursion
    // We have to explicitly cast it to const object so that compiler must call const version of operator
    // Since this function returns just reference to object we need to cast it bact to non-constant
    // That is why we use double cast to prevent duplication of code.
    return const_cast<complex::Complex &>(const_cast<const Array &>(*this)[index]);
}

const complex::Complex &Array::operator[](int index) const {
    if (index < 0 || index >= capacity) std::exit(-1);
    return data[index];
}

// Find if complex number exist in range low-high
int Array::operator()(const complex::Complex &complex, int high, int low) const {
    if (low <= 0) low = 0;
    if (low >= capacity) low = capacity-1;

    if (high <= 0) high = 0;
    if (high >= capacity) high = capacity-1;

    for (int i = low; i <= high; i++) {
        if (data[i] == complex) return i;
    }

    return -1;
}

// Find if complex number exist in array
int Array::operator()(const complex::Complex &complex) const {
    return (*this)(complex, capacity, 0);
}





