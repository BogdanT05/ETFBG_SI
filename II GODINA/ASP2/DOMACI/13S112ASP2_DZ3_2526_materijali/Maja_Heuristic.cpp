#include "Maja_Heuristic.h"

#include <cmath>
#include <stack>

Maja_Heuristic::Maja_Heuristic(int c) : c(c){}

void Maja_Heuristic::bubble_sort(const Image *img, int left, int right, SortingDirection direction) {
    for (int i = left; i <= right; i++) {
        for (int j = left; j < right - (i - left); j++) {
            int a = img->getElement(j);
            int b = img->getElement(j + 1);

            if ((direction == ASCENDING  && a > b) || (direction == DESCENDING && a < b))
                img->swapElements(j, j + 1);
        }
    }
}

int Maja_Heuristic::partition(const Image *img, int left, int right, SortingDirection direction) {
    int pivot = img->getElement(right);
    int i = left - 1;

    for (int j = left; j < right; j++) {
        int value = img->getElement(j);

        if ((direction == ASCENDING  && value < pivot) || (direction == DESCENDING && value > pivot)) {
            i++;
            img->swapElements(i, j);
        }
    }

    img->swapElements(i + 1, right);
    return i + 1;
}

void Maja_Heuristic::sort(const Image *img, SortingDirection direction) {
    int n = img->getElementCount();
    int max_depth = c * std::log2(n);

    struct Interval {
        int left, right, depth;
    };

    std::stack<Interval> stack;
    stack.push({0, n - 1, 0});

    while (!stack.empty()) {
        auto [left, right , depth] = stack.top();
        stack.pop();

        if (left >= right) continue;
        if (depth >= max_depth) {
            bubble_sort(img, left, right, direction);
            continue;
        }

        int p = partition(img, left, right, direction);

        stack.push({left, p - 1, depth + 1});
        stack.push({p + 1, right, depth + 1});
    }
}
