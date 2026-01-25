#ifndef SORTING_DATA_ARRAY_H
#define SORTING_DATA_ARRAY_H
#include <vector>
#include <Observers/Observer.h>

// This class contains everything connected to the array that is being sorted
// Also it is responsible for notifying observers that something has changed.
class Data_Array {
private:
    std::vector<Observer*> observers;
    std::vector<int> array;
public:
    Data_Array() = default;
    [[nodiscard]] int get_size() const;

    void generate_array(int capacity, int lower, int higher);
    void fill_array(int capacity);

    void state() const;
    void swap(int i, int j);
    void set(int index, int value);
    [[nodiscard]] bool compare(int i, int j) const;
    void range(int l, int r) const;

    void add_observer(Observer* observer);
};


#endif //SORTING_DATA_ARRAY_H