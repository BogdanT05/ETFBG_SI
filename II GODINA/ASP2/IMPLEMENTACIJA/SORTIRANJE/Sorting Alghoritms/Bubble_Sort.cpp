#include "Bubble_Sort.h"

// Bubble sort works by comparing 2 adjacent elements and propagates biggest of
// Remaining elements to the end/final position
void Bubble_Sort::sort(Data_Array &array) {
    for (int i = 0; i < array.get_size()-1; i++) {
        for (int j = 0; j < array.get_size()-1-i; j++) {
            if (array.compare(j, j+1)) { // array[j] > array[j+1]
                array.swap(j, j+1);
            }
        }
    }
}
