#ifndef ZADACI_ZA_VEZBU_ITERATOR_H
#define ZADACI_ZA_VEZBU_ITERATOR_H
#include "Array.h"

class Iterator {
private:
    friend class Array;
    Array &array;
    complex::Complex *pointer;

    Iterator(Array &array);
public:
    explicit Iterator (const Array& array) = delete;
    Iterator& operator = (const Array& array) = delete;

    complex::Complex* operator -> () const;
    complex::Complex& operator * () const;
    operator bool() const;
    bool operator ! () const;

    Iterator& operator ++ ();
    Iterator& operator -- ();

};


#endif //ZADACI_ZA_VEZBU_ITERATOR_H