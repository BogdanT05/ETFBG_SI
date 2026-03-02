#include "Echo_Command.h"
#include "Semantic_Error.h"
#include "Interpreter.h"

void Echo::execute(Interpreter &interpreter) {
    std::unique_ptr<Input_Stream> temp_stream;
    Input_Stream * source = resolve_input(temp_stream);

    std::string line;
    std::string result;
    while (source->read_line(line))
        result += line + '\n';

    os->write_line(result.substr(0, result.size()-1));
}

void Echo::validate() {
    if (!options.empty())
        throw Semantic_Error("echo does not accept options");

    if (arguments.size() > 1)
        throw Semantic_Error("echo accepts at most 1 argument");
}
