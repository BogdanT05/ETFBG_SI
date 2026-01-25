#include "Selection_Sort.h"

// Selection sort, in every iteration it finds current minimum and put it in correct place.
// Outer for loop shortens range of possible minimums in every iteration, inner finds minimum
void Selection_Sort::sort(Data_Array &array) {
    for (int i = 0; i < array.get_size()-1; i++) {
        int min_value = i;
        for (int j = i+1; j < array.get_size(); j++) {
            if (array.compare(min_value, j)) { // array[i] > array[j]
                min_value = j;
            }
        }
        array.swap(i, min_value);
    }
}
