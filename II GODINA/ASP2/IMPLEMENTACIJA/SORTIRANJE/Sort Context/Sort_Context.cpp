#include "Sort_Context.h"

Sort_Context::Sort_Context(Data_Array *data, Sorting_Algorithm *algorithm) : data(data), algorithm(algorithm){}

void Sort_Context::sort() const {
    data->state();
    algorithm->sort(*data);
}

void Sort_Context::set_algorithm(Sorting_Algorithm *algorithm_) {
    algorithm = algorithm_;
}

void Sort_Context::set_data(Data_Array *data_) {
    data = data_;
}
