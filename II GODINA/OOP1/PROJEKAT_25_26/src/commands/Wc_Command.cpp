#include "Wc_Command.h"
#include <memory>
#include "File_Input_Stream.h"
#include "Semantic_Error.h"

void Wc::execute(Interpreter &interpreter) {
    std::unique_ptr<Input_Stream> temp_stream;
    Input_Stream *source = resolve_input(temp_stream);

    std::size_t counter = 0;
    std::string line;

    bool count_words = (options[0] == "-w");
    bool count_char = (options[0] == "-c");

    while (source->read_line(line)) {
        if (count_char)
            counter += line.size()+1;

        if (count_words) {
            bool in_word = false;
            for (char c : line) {
                if (!std::isspace(static_cast<unsigned char>(c))) {
                    if (!in_word) {
                        counter++;
                        in_word = true;
                    }
                }
                else
                    in_word = false;
            }
        }
    }

    os->write_line(std::to_string(counter));
}

void Wc::validate() {
    if (options.size() != 1)
        throw Semantic_Error("wc requires only one option");
    if (options[0] != "-w" && options[0] != "-c")
        throw Semantic_Error("Invalid option for wc '" + options[0] + "'");
    if (arguments.size() > 1)
        throw Semantic_Error("wc accepts at most one argument");
}
