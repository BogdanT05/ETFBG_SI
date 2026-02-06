#include "Marko_Heuristic.h"

Marko_Heuristic::Marko_Heuristic(const int c) : c(c){}

void Marko_Heuristic::insertion_sort(const Image *img, int left, int right, SortingDirection direction) {
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
    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) {
        int left_value = img->getElement(i);
        int right_value = img->getElement(j);

        if ((direction == ASCENDING  && right_value < left_value) || (direction == DESCENDING && right_value > left_value)) {
            int k = j;
            while (k > i) {
                img->swapElements(k, k - 1);
                k--;
            }
            i++;
            mid++;
            j++;
        }
        else i++;
    }
}

bool Marko_Heuristic::is_nearly_sorted(const Image *img, int left, int right, SortingDirection direction) const {
    int inv = 0;

    for (int i = left; i < right; i++) {
        int a = img->getElement(i);
        int b = img->getElement(i + 1);

        if ((direction == ASCENDING && a > b) ||(direction == DESCENDING && a < b))
            inv++;
    }

    int n = right - left + 1;
    return inv <= c * n;
}

void Marko_Heuristic::sort(const Image *img, SortingDirection direction) {
    int n = img->getElementCount();
    for (int block = 1; block < n; block*=2) {
        for (int left = 0; left < n - block; left += 2 * block) {
            int mid = left + block-1;
            int right = std::min(left + 2 * block - 1, n-1);

            if (is_nearly_sorted(img, left, right, direction))
                insertion_sort(img, left, right, direction);
            else
                merge(img, left, mid, right, direction);
        }
    }
}
