#include "Tr_Command.h"
#include <memory>
#include "File_Input_Stream.h"
#include "Semantic_Error.h"

void Tr::execute(Interpreter &interpreter) {
    std::string what = options[0].substr(1);
    std::string with;
    std::string filename;

    if (arguments.size() == 1)
        filename = arguments[0];
    else if (arguments.size() == 2) {
        filename = arguments[0];
        with = arguments[1];
    }

    Input_Stream *source = nullptr;
    std::unique_ptr<File_Input_Stream> file_stream;

    if (!filename.empty()) {
        file_stream = std::make_unique<File_Input_Stream>(filename);
        source = file_stream.get();
    }
    else
        source = is;

    std::string line;
    while (source->read_line(line)) {
        std::size_t position = 0;
        while ((position = line.find(what, position)) != std::string::npos) {
            if (!with.empty()) {
                line.replace(position, what.length(), with);
                position += with.length();
            }
            else {
                line.erase(position, what.length());
            }
        }
        os->write_line(line);
    }
}

void Tr::validate() {
    if (options.size() != 1)
        throw Semantic_Error("tr requires exactly one pattern option");
    if (options[0].size() <= 1)
        throw Semantic_Error("tr pattern cannot be empty");
    if (arguments.size() > 2)
        throw Semantic_Error("tr accepts at most 2 arguments");
}
