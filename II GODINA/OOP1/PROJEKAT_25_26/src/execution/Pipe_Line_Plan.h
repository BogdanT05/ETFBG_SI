#ifndef PROJEKAT2526_PIPE_LINE_PLAN_H
#define PROJEKAT2526_PIPE_LINE_PLAN_H
#include <memory>
#include <vector>

#include "Command.h"
#include "Execution_Plan.h"


class Pipe_Line_Plan : public Execution_Plan{
private:
    std::vector<std::unique_ptr<Command>> commands;
public:
    explicit Pipe_Line_Plan(std::vector<std::unique_ptr<Command>> commands);
    void execute(Interpreter &interpreter) override;
};


#endif //PROJEKAT2526_PIPE_LINE_PLAN_H