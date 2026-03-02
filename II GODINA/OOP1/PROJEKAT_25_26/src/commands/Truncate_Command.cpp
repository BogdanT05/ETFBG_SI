#include "Truncate_Command.h"
#include <fstream>

#include "Execution_Error.h"
#include "Semantic_Error.h"


void Truncate::execute(Interpreter &interpreter) {
    std::ifstream check(arguments[0]);
    if (!check.good())
        throw Execution_Error("File does not exists '" + arguments[0] + "'");
    check.close();

    std::ofstream truncate_file(arguments[0], std::ios::trunc);
    if (!truncate_file)
        throw Execution_Error("Cannot truncate file '" + arguments[0] + "'");

    truncate_file.close();
}

void Truncate::validate() {
    if (!options.empty())
        throw Semantic_Error("truncate does not accept options");

    if (arguments.size() != 1)
        throw Semantic_Error("truncate requires exactly one argument");
}
