#ifndef PROJEKAT2526_SINGLE_COMMAND_PLAN_H
#define PROJEKAT2526_SINGLE_COMMAND_PLAN_H
#include <memory>

#include "Command.h"
#include "Execution_Plan.h"


class Single_Command_Plan : public Execution_Plan {
private:
    std::unique_ptr<Command> command;
public:
    explicit Single_Command_Plan(std::unique_ptr<Command> command);
    void execute() override;
};


#endif //PROJEKAT2526_SINGLE_COMMAND_PLAN_H