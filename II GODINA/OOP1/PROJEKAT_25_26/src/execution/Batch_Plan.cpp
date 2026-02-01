#include "Batch_Plan.h"

#include <algorithm>

#include "Error.h"
#include "Parser.h"
#include "Tokenizer.h"


Batch_Plan::Batch_Plan(Input_Stream *stream, Output_Stream *output_stream) : file(stream), output_stream(output_stream){}

void Batch_Plan::execute(Interpreter &interpreter) {
    Output_Stream *old_output = interpreter.get_output();
    interpreter.set_output(output_stream);

    std::string line;
    while (file->read_line(line)) {
        if (line.empty() || is_blank(line))
            continue;

        interpreter.execute_line(line);
    }

    interpreter.set_output(old_output);
}

void Batch_Plan::print_error(const Error &error) {
    error.print();
}

bool Batch_Plan::is_blank(const std::string &string) {
    return std::all_of(string.begin(), string.end(), [](const unsigned char c){return std::isspace(c);});
}
