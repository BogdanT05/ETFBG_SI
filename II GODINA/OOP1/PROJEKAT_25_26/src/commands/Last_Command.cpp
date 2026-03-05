#include "Last_Command.h"
#include "Interpreter.h"
#include "Semantic_Error.h"
#include "Tokenizer.h"

void Last::execute(Interpreter &interpreter) {
    std::string raw_command_last = interpreter.get_last_command();

    if (raw_command_last.empty())
        throw Semantic_Error("No previous command");

    interpreter.execute_line(raw_command_last);
}

void Last::validate() {
    if (!is->is_console())
        throw Semantic_Error("last does not allow input redirection");

    if (!arguments.empty())
        throw Semantic_Error("last does not accept arguments");

    if (!options.empty()) {
        throw Semantic_Error("last does not accept options");
    }
}
