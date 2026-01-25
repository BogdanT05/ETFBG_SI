#ifndef SORTING_SORTING_ALGORITHM_H
#define SORTING_SORTING_ALGORITHM_H
#include "Data Arrays/Data_Array.h"

//Abstract class that will be parental class to all sorting Algorithms
class Sorting_Algorithm {
public:
    virtual void sort(Data_Array &array) = 0;
    virtual ~Sorting_Algorithm() = default;
};


#endif //SORTING_SORTING_ALGORITHM_H