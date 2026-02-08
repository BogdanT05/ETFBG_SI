#ifndef MARKO_HEURISTIC_H
#define MARKO_HEURISTIC_H
#include "sorting.h"

// Markova heuristika predstavlja spoj merge sorta i insertion sorta
// Merge sort se radi dok particija nije skoro sortirana nakon cega se ona sortira
// sa insertion sortom, particija je skoro sortirana kada je broj inverzija < n * c
// gde je c proizvoljna konstanta
class Marko_Heuristic : public SortingAlgorithm {
private:
    int c;

    static void insertion_sort(const Image *img, int left, int right, SortingDirection direction);
    static void merge(const Image *img, int left, int mid, int right, SortingDirection direction);
    bool is_nearly_sorted(const Image *img, int left, int right, SortingDirection direction) const;
public:
    explicit Marko_Heuristic(int c);
    void sort(const Image *img, SortingDirection direction) override;
};


#endif //MARKO_HEURISTIC_H