#include "Rm_Command.h"
#include <fstream>
#include <cstdio>
#include "Execution_Error.h"
#include "IOError.h"
#include "Semantic_Error.h"

void Rm::execute(Interpreter &interpreter) {
    std::ifstream check(arguments[0]);
    if (!check.good())
        throw Execution_Error("File does not exists '" + arguments[0] + "'");
    check.close();

    if (std::remove(arguments[0].c_str()) != 0)
        throw IOError("Cannot remove file '" + arguments[0] + "'");
}

void Rm::validate() {
    if (!options.empty())
        throw Semantic_Error("rm does not accept options");

    if (arguments.size() != 1)
        throw Semantic_Error("rm requires exactly one argument");
}
