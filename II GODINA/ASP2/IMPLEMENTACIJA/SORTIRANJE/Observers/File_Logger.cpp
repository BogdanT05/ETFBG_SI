#include "File_Logger.h"
#include <fstream>

File_Logger::File_Logger(std::ofstream &ofs) : ofs(ofs), step_counter(0) {}

void File_Logger::on_state(const std::vector<int>& state) {
    ofs << "Array state: [ ";
    for (size_t i = 0; i < state.size(); i++) {
        ofs << state[i];
        if (i + 1 < state.size()) ofs << " ";
    }
    ofs << " ]\n";
}

void File_Logger::on_compare(int i, int j) {
    ofs << "----------------------------------------\n";
    ofs << "Step " << step_counter++ << "\n";
    ofs << "Compare indices: i=" << i << ", j=" << j << "\n";
}

void File_Logger::on_swap(int i, int j) {
    ofs << "----------------------------------------\n";
    ofs << "Step " << step_counter++ << "\n";
    ofs << "Swap indices: i=" << i << ", j=" << j << "\n";
}

void File_Logger::on_set(int index, int value) {
    ofs << "----------------------------------------\n";
    ofs << "Step " << step_counter++ << "\n";
    ofs << "Set value at index " << index << " to " << value << "\n";
}

void File_Logger::on_range(int l, int r) {
    ofs << "Current range: [" << l << ", " << r << "]\n";
}

