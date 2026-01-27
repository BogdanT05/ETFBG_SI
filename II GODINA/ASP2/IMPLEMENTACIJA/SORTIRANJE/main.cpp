#include "Sorting Alghoritms/sorting_algorithms.h"
#include "Data Arrays/Data_Array.h"
#include "Sort Context/Sort_Context.h"
#include "Observers/File_Logger.h"
#include "Observers/Observer.h"
#include <fstream>

int main() {
    constexpr int N = 20;

    Data_Array data_bubble;
    data_bubble.generate_array(N, 0, 100);

    std::ofstream ofs1("Bubble_Sort.txt");
    File_Logger logger1(ofs1);
    data_bubble.add_observer(&logger1);

    Bubble_Sort bubble;
    Sort_Context ctx1(&data_bubble, &bubble);
    ctx1.sort();


    // ===== Heap Sort =====
    Data_Array data_heap;
    data_heap.generate_array(N, 0, 100);

    std::ofstream ofs2("Heap_Sort.txt");
    File_Logger logger2(ofs2);
    data_heap.add_observer(&logger2);

    Heap_Sort heap;
    Sort_Context ctx2(&data_heap, &heap);
    ctx2.sort();


    // ===== Insertion Sort =====
    Data_Array data_insertion;
    data_insertion.generate_array(N, 0, 100);

    std::ofstream ofs3("Insertion_Sort.txt");
    File_Logger logger3(ofs3);
    data_insertion.add_observer(&logger3);

    Insertion_Sort insertion;
    Sort_Context ctx3(&data_insertion, &insertion);
    ctx3.sort();


    // ===== Selection Sort =====
    Data_Array data_selection;
    data_selection.generate_array(N, 0, 100);

    std::ofstream ofs4("Selection_Sort.txt");
    File_Logger logger4(ofs4);
    data_selection.add_observer(&logger4);

    Selection_Sort selection;
    Sort_Context ctx4(&data_selection, &selection);
    ctx4.sort();


    // ===== Shake Sort =====
    Data_Array data_shake;
    data_shake.generate_array(N, 0, 100);

    std::ofstream ofs5("Shake_Sort.txt");
    File_Logger logger5(ofs5);
    data_shake.add_observer(&logger5);

    Shake_Sort shake;
    Sort_Context ctx5(&data_shake, &shake);
    ctx5.sort();


    // ===== Shell Sort =====
    Data_Array data_shell;
    data_shell.generate_array(N, 0, 100);

    std::ofstream ofs6("Shell_Sort.txt");
    File_Logger logger6(ofs6);
    data_shell.add_observer(&logger6);

    Shell_Sort shell;
    Sort_Context ctx6(&data_shell, &shell);
    ctx6.sort();


    // ===== Quick Sort =====
    Data_Array data_quick;
    data_quick.generate_array(N, 0, 100);

    std::ofstream ofs7("Quick_Sort.txt");
    File_Logger logger7(ofs7);
    data_quick.add_observer(&logger7);

    Quick_Sort quick;
    Sort_Context ctx7(&data_quick, &quick);
    ctx7.sort();


    // ===== Radix Sort =====
    Data_Array data_radix;
    data_radix.generate_array(N, 0, 100);

    std::ofstream ofs8("Radix_Sort.txt");
    File_Logger logger8(ofs8);
    data_radix.add_observer(&logger8);

    Radix_Sort radix;
    Sort_Context ctx8(&data_radix, &radix);
    ctx8.sort();

    return 0;
}