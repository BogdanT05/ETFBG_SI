#ifndef DZ2_SCHEDULER_H
#define DZ2_SCHEDULER_H
#include "Tree234.h"

class Scheduler {
private:
    Tree234 *tree234;
    int time_slice;
public:
    explicit Scheduler(Tree234 *tree234 = nullptr, int time_slice = 100) :
    tree234(tree234),
    time_slice(time_slice){}

    void step(std::ostream &os);
    void run(std::ostream &os);
};


#endif //DZ2_SCHEDULER_H