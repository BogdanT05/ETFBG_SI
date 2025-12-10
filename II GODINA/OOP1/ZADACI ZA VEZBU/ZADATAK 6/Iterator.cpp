#include "Iterator.h"

Iterator::Iterator(Array &array) : array(array), pointer(array.data){}

Iterator Array::get_iterator(){
    return Iterator(*this);
}

complex::Complex *Iterator::operator->() const {
    return pointer;
}

complex::Complex &Iterator::operator*() const {
    return *pointer;
}

Iterator::operator bool() const {
    return pointer >= array.data && pointer < array.data + array.capacity;
}

bool Iterator::operator!() const {
    return *this == false;
}

Iterator &Iterator::operator++() {
    ++pointer;
    return *this;
}

Iterator &Iterator::operator--() {
    --pointer;
    return *this;
}




