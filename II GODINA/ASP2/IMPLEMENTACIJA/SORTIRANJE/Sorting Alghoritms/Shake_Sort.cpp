#include "Shake_Sort.h"

// Shake sort, Bubble sort but alternatig direction of sorting
// Finding biggest, then smallest element in array
void Shake_Sort::sort(Data_Array &array) {
    int left = 0;
    int right = array.get_size()-1;

    while (left < right) {
        for (int i = left; i < right; i++)
            if (array.compare(i, i+1)) array.swap(i, i+1);
        right -= 1;

        for (int i = right; i > left; i--)
            if (array.compare(i-1, i)) array.swap(i-1, i);
        left += 1;
    }
}
