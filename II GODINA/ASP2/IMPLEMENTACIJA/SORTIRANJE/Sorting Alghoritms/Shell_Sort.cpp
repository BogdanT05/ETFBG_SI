#include "Shell_Sort.h"
#include <vector>

// Shell sort, improved Selection Sort that divides array in sections, that are on equal distance
// From one another and sorts each section using Selection sort, for example if array.size() = 8
// First sections are with increment 4. Firstly its sorting nums at index 0, 4
// After that increment 2, sorting elements at index 0, 2, 4, 6
// Etc...
void Shell_Sort::sort(Data_Array &array) {

    std::vector<int> increments_vector = increment_array(array.get_size());
    for (int i = 0; i < increments_vector.size(); i++) {
        int increment = increments_vector[i];
        for (int j = increment; j < array.get_size(); j++) {
            int y = array.get(j);
            int k = j - increment;

            while (k >= 0 && y < array.get(k)) {
                array.set(k+increment, array.get(k));
                k = k - increment;
            }

            array.set(k+increment, y);
        }
    }
}

std::vector<int> Shell_Sort::increment_array(int size) {
    std::vector<int> increments;
    int increment = size;

    while (increment > 0) increments.push_back(increment /= 2);

    return increments;
}
