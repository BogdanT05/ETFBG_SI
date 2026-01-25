#include "Insertion_Sort.h"

// Insertion sort, works by dividing array in two sections, sorted and unsorted.
// Sorted section is gradually increasing in every iteration of outer for loop.
// First element of unsorted section is key element and we are finding his correct position.
// By comparing it with elements of sorted section and moving them accordingly until we find right positon.
// We are repeating this process until we sort whole array.
void Insertion_Sort::sort(Data_Array &array) {
    for (int i = 1; i < array.get_size(); i++) {
        int key = array.get(i);
        int j = i - 1;

        while (j > -1 && array.get(j) > key) {
            array.set(j+1, array.get(j));
            j = j - 1;
        }
        array.set(j+1, key);
    }
}
