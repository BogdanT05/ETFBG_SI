#include "Head_Command.h"

#include <memory>

#include "File_Input_Stream.h"
#include "Semantic_Error.h"

void Head::execute(Interpreter &interpreter) {
    int num_lines = std::stoi(options[0].substr(2));
    std::string filename;

    if (!arguments.empty())
        filename = arguments[0];

    Input_Stream *source = nullptr;
    std::unique_ptr<File_Input_Stream> file_stream;

    if (!filename.empty()) {
        file_stream = std::make_unique<File_Input_Stream>(filename);
        source = file_stream.get();
    }
    else
        source = is;

    std::string line;
    int count = 0;
    while (count < num_lines && source->read_line(line)) {
        os->write_line(line);
        count++;
    }
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
