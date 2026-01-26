#ifndef SORTING_HEAP_SORT_H
#define SORTING_HEAP_SORT_H
#include "Sorting_Algorithm.h"


class Heap_Sort : Sorting_Algorithm {
public:
    void sort(Data_Array &array) override;
    static void make_heap(Data_Array &array) ;
    static void heapify(Data_Array &array, int heap_size, int index) ;
};


#endif //SORTING_HEAP_SORT_H