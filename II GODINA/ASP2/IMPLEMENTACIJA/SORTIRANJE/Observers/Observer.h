#ifndef DZ2_OBSERVER_H
#define DZ2_OBSERVER_H

// Abstract class that will be parental class to all other observers
// It's methods are reactions to standard operations when sorting arrays

class Observer {
public:
    virtual void on_swap(int i, int j) = 0;
    virtual void on_set(int index, int value) = 0;
    virtual void on_compare(int i, int j) = 0;
    virtual void on_range(int l, int r) = 0;

    virtual ~Observer() = default;
};

#endif //DZ2_OBSERVER_H