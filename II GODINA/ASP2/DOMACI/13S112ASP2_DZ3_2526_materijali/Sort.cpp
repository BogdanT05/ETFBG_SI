#include "Sort.h"
#include <algorithm>
#include <vector>

void Std_Sort::sort(const Image *img, SortingDirection direction) {
    int n = img->getElementCount();

    std::vector<int> position(n);
    for (int i = 0 ; i < n; i++)
        position[i] = i;

    std::sort(position.begin(), position.end(), [&](int a, int b) {
        int value_a = img->getElement(a);
        int value_b = img->getElement(b);
        return (direction == ASCENDING)?(value_a < value_b):(value_a > value_b);
    });

    for (int i = 0; i < n; i++) {
        while (position[i] != i) {
            int j = position[i];
            img->swapElements(i, j);
            std::swap(position[i], position[j]);
        }
    }
}
