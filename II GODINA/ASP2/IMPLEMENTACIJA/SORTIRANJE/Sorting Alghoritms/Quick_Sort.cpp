#include "Quick_Sort.h"
#include <stack>

// Quick sort, divide and conquer, divide array in partitions where everything left of pivot is
// Smaller than pivot and everything right of pivot is greater than pivot.
// We repeat that process by dividing partitions in smaller partitions until its size is trivial (1)
void Quick_Sort::sort(Data_Array &array) {
    int n = array.get_size();
    std::stack<std::pair<int, int>> stack;
    stack.emplace(0, n-1);

    while (!stack.empty()) {
        auto[low, high] = stack.top();
        stack.pop();

        while (low < high) {
            int p = partition(array, low, high);
            int left_size = p - 1 - low;
            int right_size = high - (p+1);

            if (left_size > right_size) {
                if (low < p-1) stack.emplace(low, p-1);
                low = p + 1;
            }else {
                if (p+1 < high) stack.emplace(p+1, high);
                high = p - 1;
            }
        }
    }
}

int Quick_Sort::partition(Data_Array &array, int low, int high) {
    int mid = (low + high)/2;
    array.swap(mid, high);
    int pivot = array.get(high);

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (array.get(j) <= pivot) {
            i++;
            array.swap(i, j);
        }
    }

    array.swap(i+1, high);
    return i+1;
}
