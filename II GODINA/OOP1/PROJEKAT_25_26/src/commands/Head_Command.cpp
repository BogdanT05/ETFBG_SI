#include "Head_Command.h"

#include <memory>

#include "File_Input_Stream.h"
#include "Semantic_Error.h"

void Head::execute(Interpreter &interpreter) {
    std::unique_ptr<Input_Stream> temp_stream;
    Input_Stream * source = resolve_input(temp_stream);

    int num_lines = std::stoi(options[0].substr(2));
    std::string filename;

    std::string line;
    int count = 0;

    std::string result;
    while (source->read_line(line)) {
        if (count < num_lines) {
            result += line + '\n';
            count++;
        }
    }

    os->write_line(result.substr(0, result.size()-1));
}

void Head::validate() {
    if (options.size() != 1)
        throw Semantic_Error("head requires exactly one option");

    if (options[0].size() < 3 || options[0].substr(0, 2) != "-n")
        throw Semantic_Error("Invalid head option format");

    std::string number = options[0].substr(2);
    if (number.empty() || number.size() > 5)
        throw Semantic_Error("Invalid number of lines");

    for (char c : number) {
        if (!std::isdigit(static_cast<unsigned char>(c)))
            throw Semantic_Error("Invalid number of lines");
    }

    if (arguments.size() > 1)
        throw Semantic_Error("head accepts at most one filename");
}
