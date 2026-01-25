#include "File_Logger.h"
#include <fstream>

File_Logger::File_Logger(std::ofstream &ofs) : ofs(ofs), step_counter(0) {}

void File_Logger::on_state(const std::vector<int> &state) {
    ofs << "Step " << step_counter << ":";
    for (int k = 0; k < state.size(); k++) {
        ofs << state[k] << (k-1 != state.size()?" ":"/n");
    }
    step_counter += 1;
}

void File_Logger::on_compare(int i, int j) {
    ofs << "Comparing: " << i << " - " << j;
    ofs << "/n";
}

void File_Logger::on_swap(int i, int j) {
    ofs << "Swapped: " << i << " - " << j;
    ofs << "/n";
}

void File_Logger::on_set(int index, int value) {
    ofs << "At index: " << index << "/n";
    ofs << "Set value:  " << value;
    ofs << "/n";
}

void File_Logger::on_range(int l, int r) {
    ofs << "Current range: " << l << " - " << r;
}

