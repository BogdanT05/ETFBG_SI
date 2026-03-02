#include "Tr_Command.h"
#include <memory>
#include "File_Input_Stream.h"
#include "Semantic_Error.h"
#include "Token.h"

void Tr::execute(Interpreter &interpreter) {
    std::unique_ptr<Input_Stream> temp_stream;
    Input_Stream *source = resolve_input(temp_stream);

    std::string what = options[0].substr(2, options[0].size()-3);
    if (what.empty())
        throw Semantic_Error("tr cannot operate on empty string");
    std::string with;
    bool replace = false;

    if (arguments.size() ==2) {
        with = arguments[1].value;
        replace = true;
    }

    std::string line;
    std::string result;
    while (source->read_line(line)) {
        std::size_t position = 0;
        while ((position = line.find(what, position)) != std::string::npos) {
            if (replace) {
                line.replace(position, what.length(), with);
                position += with.length();
            }
            else {
                line.erase(position, what.length());
            }
        }
        result += line + '\n';
    }
    os->write_line(result.substr(0, result.size()-1));
}

void Tr::validate() {
    if (options.size() != 1)
        throw Semantic_Error("tr requires exactly one pattern option");
    if (options[0].size() < 3 || options[0][0] != '-' || options[0][1] != '"' || options[0].back() != '"')
        throw Semantic_Error("Invalid tr pattern format");
    if (arguments.size() > 2)
        throw Semantic_Error("tr accepts at most 2 arguments");
    if (arguments.size() == 2 && arguments[1].type != Token_type::STRING)
        throw Semantic_Error("Replacement must be string literal");
}
