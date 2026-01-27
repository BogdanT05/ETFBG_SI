#ifndef SORTING_RADIX_SORT_H
#define SORTING_RADIX_SORT_H
#include "Sorting_Algorithm.h"


class Radix_Sort : Sorting_Algorithm{
public:
    void sort(Data_Array &array) override;

    static void counting_sort(Data_Array &array, int exponent);
    static int get_max(const Data_Array &array);
};


#endif //SORTING_RADIX_SORT_H