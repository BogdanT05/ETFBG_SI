#ifndef PROJEKAT2526_EXECUTION_PLAN_H
#define PROJEKAT2526_EXECUTION_PLAN_H
#include "Interpreter.h"

// Abstract class for execution plans
// Execution plan represent way of interaction between commands

class Execution_Plan {
public:
    virtual void execute(Interpreter &interpreter) = 0;
    virtual ~Execution_Plan() = default;
};


#endif //PROJEKAT2526_EXECUTION_PLAN_H