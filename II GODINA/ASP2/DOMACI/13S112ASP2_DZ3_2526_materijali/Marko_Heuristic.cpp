#include "Marko_Heuristic.h"

void Marko_Heuristic::insertion_sort(Image *img, int left, int right, SortingDirection direction) {
    for (int i = left + 1; i <= right; i++) {
        int j = i;
        while (j > left) {
            int a = img->getElement(j - 1);
            int b = img->getElement(j);

            if ((direction == ASCENDING && a > b) || (direction == DESCENDING && a < b)) {
                img->swapElements(j - 1, j);
                j--;
            } else break;
        }
    }
}

void Marko_Heuristic::merge(const Image *img, int left, int mid, int right, SortingDirection direction) {

}

bool Marko_Heuristic::is_nearly_sorted(Image *img, int left, int right, SortingDirection direction) {
}

Marko_Heuristic::Marko_Heuristic(const int c) : c(c){}

void Marko_Heuristic::sort(Image *image, SortingDirection direction) {
}
