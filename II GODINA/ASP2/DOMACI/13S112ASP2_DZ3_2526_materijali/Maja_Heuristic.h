#ifndef MAJA_HEURISTIC_H
#define MAJA_HEURISTIC_H
#include "sorting.h"

// Majina heuristika zasniva se na kombinaciji quick sorta i bubble sorta
// Quick sort se izvrsava dok je dubina manja od c * log2n gde je c proizvoljna
// Konstanta a n velicina same particije.
class Maja_Heuristic : public SortingAlgorithm{
private:
    int c;
    static void bubble_sort(const Image *img, int left, int right, SortingDirection direction);
    static int partition(const Image *img, int left, int right, SortingDirection direction);

public:
    explicit Maja_Heuristic(int c);
    void sort(const Image *img, SortingDirection direction) override;
};


#endif //MAJA_HEURISTIC_H