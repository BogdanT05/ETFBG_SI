#include "Prompt_Command.h"
#include "Interpreter.h"
#include "Semantic_Error.h"

void Prompt::execute(Interpreter &interpreter) {
    interpreter.set_prompt(arguments[0]);
}

void Prompt::validate() {
    if (!options.empty())
        throw Semantic_Error("prompt does not accept options");

    if (arguments.size() != 1)
        throw Semantic_Error("prompt requires exactly one argument");
}
