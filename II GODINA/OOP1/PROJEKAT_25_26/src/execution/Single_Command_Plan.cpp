#include "Single_Command_Plan.h"
#include "Command.h"
Single_Command_Plan::Single_Command_Plan(std::unique_ptr<Command> command) : command(std::move(command)) {}

void Single_Command_Plan::execute(Interpreter &interpreter) {
    if (!command->get_output())
        command->set_output(interpreter.get_output());

    command->execute(interpreter);
}
