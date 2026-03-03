#ifndef PROJEKAT2526_PIPE_LINE_PLAN_H
#define PROJEKAT2526_PIPE_LINE_PLAN_H
#include <memory>
#include <memory>
#include <vector>
#include "Command.h"
#include "Execution_Plan.h"
#include "Pipe_Buffer.h"

// Class that is used to connect pipes

class Pipe_Line_Plan : public Execution_Plan{
private:
    std::vector<std::unique_ptr<Command>> commands;
public:
    explicit Pipe_Line_Plan(std::vector<std::unique_ptr<Command>> commands);
    void execute(Interpreter &interpreter) override;

    std::vector<std::unique_ptr<Pipe_Buffer>> create_buffers() const;

    void connect_commands(const std::vector<std::unique_ptr<Pipe_Buffer>> &buffers) const;

    void execute_commands(Interpreter &interpreter) const;
};


#endif //PROJEKAT2526_PIPE_LINE_PLAN_H