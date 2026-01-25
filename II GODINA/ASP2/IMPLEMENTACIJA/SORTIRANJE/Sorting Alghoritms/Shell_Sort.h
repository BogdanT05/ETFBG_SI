#ifndef SORTING_SHELL_SORT_H
#define SORTING_SHELL_SORT_H
#include "Sorting_Algorithm.h"
#include <vector>

class Shell_Sort : Sorting_Algorithm{
public:
    void sort(Data_Array &array) override;

    static std::vector<int> increment_array(int size);
};


#endif //SORTING_SHELL_SORT_H