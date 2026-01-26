#include "Heap_Sort.h"
// Heap Sort is based on heap structure, where parent value is always greater than its sons
// So to sort array we take the root of heap which and send it to the back of array
// And then readjust the heap and repeat that proces until whole array is sorted
void Heap_Sort::sort(Data_Array &array) {
    int heap_size = array.get_size();
    for (int i = array.get_size()-1; i > 0; i--) {
        array.swap(0, i);
        heapify(array, --heap_size, 0);
    }
}

void Heap_Sort::make_heap(Data_Array &array) {
    for (int i = array.get_size()/2-1; i >= 0; i--)
        heapify(array, array.get_size(), i);
}

void Heap_Sort::heapify(Data_Array &array, int heap_size, int index) {
    while (true) {
        int largest = index;
        int left = 2*largest + 1;
        int right = 2*largest + 2;

        if (left < heap_size && array.get(left) > array.get(largest)) largest = left;
        if (right < heap_size && array.get(right) > array.get(largest)) largest = right;
        if (largest == index) return;

        array.swap(largest, index);
        index = largest;
    }
}

