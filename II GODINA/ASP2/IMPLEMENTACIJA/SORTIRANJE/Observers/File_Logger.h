#ifndef SORTING_FILE_LOGGER_H
#define SORTING_FILE_LOGGER_H
#include "Observer.h"
#include <iostream>
#include <vector>

class File_Logger : Observer{
    std::ofstream &ofs;
    int step_counter;
public:
    explicit File_Logger(std::ofstream &ofs);

    void on_state(const std::vector<int>& state) override;
    void on_compare(int i, int j) override;
    void on_swap(int i, int j) override;
    void on_set(int index, int value) override;
    void on_range(int l, int r) override;

    ~File_Logger() override = default;
};


#endif //SORTING_FILE_LOGGER_H
