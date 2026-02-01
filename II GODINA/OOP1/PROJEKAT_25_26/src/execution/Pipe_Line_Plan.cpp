#include "Pipe_Line_Plan.h"

#include "Pipe_Buffer.h"
#include "Pipe_Input_Stream.h"
#include "Pipe_Output_Stream.h"

Pipe_Line_Plan::Pipe_Line_Plan(std::vector<std::unique_ptr<Command>> commands) : commands(std::move(commands)){}

void Pipe_Line_Plan::execute(Interpreter &interpreter) {
    if (commands.size() == 1) {
        commands[0]->execute();
        return;
    }

    std::vector<std::unique_ptr<Pipe_Buffer>> buffers;
    buffers.reserve(commands.size()-1);

    for (std::size_t i = 0; i < commands.size()-1; i++) {
        buffers.push_back(std::make_unique<Pipe_Buffer>());
    }

    for (std::size_t i = 0; i < commands.size(); i++) {
        if (i > 0) {
            auto *in = new Pipe_Input_Stream(buffers[i-1].get());
            commands[i]->set_input(in);
        }

        if (i < commands.size()-1) {
            auto *out = new Pipe_Output_Stream(buffers[i].get());
            commands[i]->set_output(out);
        }
    }

    for (const auto & command : commands)
        command->execute();
}
