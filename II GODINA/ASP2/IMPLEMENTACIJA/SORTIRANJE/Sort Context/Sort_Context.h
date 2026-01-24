#ifndef SORTING_SORT_CONTEXT_H
#define SORTING_SORT_CONTEXT_H
#include <Data Arrays/Data_Array.h>
#include <Sorting Alghoritms/Sorting_Algorithm.h>

class Sort_Context {
private:
    Data_Array *data;
    Sorting_Algorithm *algorithm;
public:
    Sort_Context(Data_Array *data, Sorting_Algorithm *algorithm);

    void sort() const;
    void set_algorithm(Sorting_Algorithm* algorithm_);
    void set_data(Data_Array *data_);
};


#endif //SORTING_SORT_CONTEXT_H