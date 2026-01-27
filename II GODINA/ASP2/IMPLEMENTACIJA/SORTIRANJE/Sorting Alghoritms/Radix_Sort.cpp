#include "Radix_Sort.h"
#include <vector>

void Radix_Sort::sort(Data_Array &array) {
    int max = get_max(array);

    for (int i = 1; max/i > 0; i*= 10) {
        counting_sort(array, i);
    }
}

void Radix_Sort::counting_sort(Data_Array &array, int exponent) {
    int n = array.get_size();
    std::vector<int> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        int digit = (array.get(i) / exponent) % 10;
        count[digit]++;
    }

    for (int i = 1; i < 10; i++)
        count[i] += count[i-1];

    for (int i = n - 1; i >= 0; i--) {
        int value = array.get(i);
        int digit = (value/exponent) % 10;
        output[count[digit] - 1] = value;
        count[digit]--;
    }

    for (int i = 0; i < n; i++) array.set(i, output[i]);
}

int Radix_Sort::get_max(const Data_Array &array) {
    int max = array.get(0);
    for (int i = 0; i < array.get_size(); i++) {
        if (array.get(i) > max) max = array.get(i);
    }

    return max;
}
