#ifndef PROJEKAT2526_EXECUTION_PLAN_H
#define PROJEKAT2526_EXECUTION_PLAN_H
#include "Interpreter.h"


class Execution_Plan {
public:
    virtual void execute(Interpreter &interpreter) = 0;
    virtual ~Execution_Plan() = default;
};


#endif //PROJEKAT2526_EXECUTION_PLAN_H