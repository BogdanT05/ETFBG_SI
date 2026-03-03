#include "Touch_Command.h"
#include "Execution_Error.h"
#include "Semantic_Error.h"
#include <fstream>

#include "IOError.h"

void Touch::execute(Interpreter &interpreter) {
    std::ifstream file(arguments[0].value);
    if (file.good())
        throw Execution_Error("File already exists '" + arguments[0].value + "'");

    file.close();
    std::ofstream create(arguments[0].value);
    if (!create)
        throw IOError("Cannot create file '" + arguments[0].value + "'");

    create.close();
}

void Touch::validate() {
    if (!is->is_console())
        throw Semantic_Error("touch does not allow input redirection");

    if (!options.empty())
        throw Semantic_Error("touch does not accept options");

    if (arguments.size() != 1)
        throw Semantic_Error("touch requires exactly one argument");
}
