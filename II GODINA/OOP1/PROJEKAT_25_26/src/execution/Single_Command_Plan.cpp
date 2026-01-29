#include "Single_Command_Plan.h"

Single_Command_Plan::Single_Command_Plan(std::unique_ptr<Command> command) : command(std::move(command)) {}

void Single_Command_Plan::execute() {
    command->execute();
}
