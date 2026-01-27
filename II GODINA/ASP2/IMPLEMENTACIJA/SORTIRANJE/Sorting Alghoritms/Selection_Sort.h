#ifndef SORTING_SELECTION_SORT_H
#define SORTING_SELECTION_SORT_H
#include "Sorting_Algorithm.h"


class Selection_Sort : public Sorting_Algorithm{
public:
    void sort(Data_Array &array) override;
};


#endif //SORTING_SELECTION_SORT_H