#ifndef DZ2_SCHEDULER_H
#define DZ2_SCHEDULER_H
#include "Tree234.h"

class Scheduler {
private:
    Tree234 *tree234;
    int time_slice;
public:
    explicit Scheduler(Tree234* tree234, int time_slice = 200) :
    tree234(tree234),
    time_slice(time_slice){}

    bool step(std::ostream &os) const;
    void run(std::ostream &os) const;
};


#endif //DZ2_SCHEDULER_H