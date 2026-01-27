#ifndef SORTING_QUICK_SORT_H
#define SORTING_QUICK_SORT_H
#include "Sorting_Algorithm.h"


class Quick_Sort : Sorting_Algorithm {
public:
    void sort(Data_Array &array) override;
    static int partition(Data_Array &array, int low, int high);
};


#endif //SORTING_QUICK_SORT_H