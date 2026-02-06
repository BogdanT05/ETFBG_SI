#ifndef MAJA_HEURISTIC_H
#define MAJA_HEURISTIC_H
#include "sorting.h"


class Maja_Heuristic : public SortingAlgorithm{
private:
    int c;
    void bubble_sort(Image *img, int left, int right, SortingDirection direction);
    int partition(Image *img, int left, int right, SortingDirection direction);

public:
    explicit Maja_Heuristic(int c);
    void sort(Image *image, SortingDirection direction) override;
};


#endif //MAJA_HEURISTIC_H