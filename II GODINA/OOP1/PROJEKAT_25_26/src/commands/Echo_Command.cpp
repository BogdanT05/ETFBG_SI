#include "Echo_Command.h"
#include "Semantic_Error.h"
#include "Interpreter.h"

void Echo::execute(Interpreter &interpreter) {
    std::string result;
    for (std::size_t i = 0; i < arguments.size(); i++) {
        if (i != arguments.size()-1)
            result += arguments[i] + " ";
        else
            result += arguments[i];
    }

    os->write_line(result);
}

void Echo::validate() {
    if (!options.empty())
        throw Semantic_Error("echo does not accept options");
}
