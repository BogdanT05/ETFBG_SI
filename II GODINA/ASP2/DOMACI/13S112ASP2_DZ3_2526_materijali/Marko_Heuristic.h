#ifndef PROJEKAT2526_MARKO_HEURISTIC_H
#define PROJEKAT2526_MARKO_HEURISTIC_H
#include "sorting.h"

class Marko_Heuristic : public SortingAlgorithm {
private:
    int c;

    static void insertion_sort(const Image *img, int left, int right, SortingDirection direction);
    static void merge(const Image *img, int left, int mid, int right, SortingDirection direction);
    bool is_nearly_sorted(const Image *img, int left, int right, SortingDirection direction) const;
public:
    explicit Marko_Heuristic(int c);
    void sort(Image *img, SortingDirection direction) override;
};


#endif //PROJEKAT2526_MARKO_HEURISTIC_H