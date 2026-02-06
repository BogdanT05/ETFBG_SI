#ifndef ASP_DZ3_SORT_H
#define ASP_DZ3_SORT_H
#include "sorting.h"


class Std_Sort : public SortingAlgorithm{
public:
    void sort(const Image *img, SortingDirection direction) override;
};


#endif //ASP_DZ3_SORT_H