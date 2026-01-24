cmake_minimum_required(VERSION 3.10)
project("Sorting")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Sorting
        main.cpp
        "Sorting Alghoritms/Sorting_Algorithm.cpp"
        "Sorting Alghoritms/Sorting_Algorithm.h"
        "Sorting Alghoritms/Selection_Sort.cpp"
        "Sorting Alghoritms/Selection_Sort.h"
        "Sorting Alghoritms/Bubble_Sort.cpp"
        "Sorting Alghoritms/Bubble_Sort.h"
        "Sorting Alghoritms/Shake_Sort.cpp"
        "Sorting Alghoritms/Shake_Sort.h"
        "Sorting Alghoritms/Insertion_Sort.cpp"
        "Sorting Alghoritms/Insertion_Sort.h"
        "Sorting Alghoritms/Shell_Sort.cpp"
        "Sorting Alghoritms/Shell_Sort.h"
        "Sorting Alghoritms/Heap_Sort.cpp"
        "Sorting Alghoritms/Heap_Sort.h"
        "Sorting Alghoritms/Quick_Sort.cpp"
        "Sorting Alghoritms/Quick_Sort.h"
        "Sorting Alghoritms/Radix_Sort.cpp"
        "Sorting Alghoritms/Radix_Sort.h"
        "Sorting Alghoritms/Counting_Sort.cpp"
        "Sorting Alghoritms/Counting_Sort.h"
        Observers/Console_Logger.cpp
        Observers/Console_Logger.h
        Sort_Context.cpp
        Sort_Context.h
)