#include "Tr_Command.h"
#include <memory>
#include "File_Input_Stream.h"
#include "Semantic_Error.h"
#include "String_Input_Stream.h"
#include "Token.h"

void Tr::execute(Interpreter &interpreter) {
    std::unique_ptr<Input_Stream> temp_stream;
    Input_Stream *source = resolve_input(temp_stream);

    std::string with;
    bool replace = false;

    int pattern_index = -1;
    find_pattern(pattern_index);

    std::string what = arguments[pattern_index].value.substr(2,
                     arguments[pattern_index].value.size() - 3);

    if (pattern_index < arguments.size() - 1) {
        with = arguments[pattern_index+1].value;
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
    if (arguments.empty())
        throw Semantic_Error("tr requires a pattern");

    if (arguments.size() > 3)
        throw Semantic_Error("tr accepts at most 3 arguments");

    int pattern_index = -1;
    find_pattern(pattern_index);

    if (pattern_index == -1)
        throw Semantic_Error("Pattern is missing");

    std::string pattern = arguments[pattern_index].value;
    std::string what = pattern.substr(2, pattern.size() - 3);

    if (what.empty())
        throw Semantic_Error("Pattern cannot be empty");

    if (pattern_index > 1)
        throw Semantic_Error("Invalid input position");

    if (pattern_index < arguments.size() - 1) {
        if (arguments.size() - pattern_index > 2)
            throw Semantic_Error("Too many arguments after pattern");

        if (arguments[pattern_index + 1].type != Token_type::STRING)
            throw Semantic_Error("Replacement must be string literal");
    }
}

void Tr::find_pattern(int &pattern_index) const {
    for (int i = 0; i < arguments.size(); i++) {
        std::string val = arguments[i].value;
        if (val.size() >= 4 && val[0] == '-' && val[1] == '"' && val.back() == '"') {
            if (pattern_index != -1)
                throw Semantic_Error("Multiple patterns are not allowed");

            pattern_index = i;
        }
    }
}

Input_Stream * Tr::resolve_input(std::unique_ptr<Input_Stream> &stream) {
    int pattern_index = -1;
    find_pattern(pattern_index);

    if (pattern_index > 0) {
        const auto& [value, type] = arguments[0];

        if (type == Token_type::STRING)
            stream = std::make_unique<String_Input_Stream>(value);
        else if (type == Token_type::WORD)
            stream = std::make_unique<File_Input_Stream>(value);
        else
            throw Semantic_Error("Invalid input for tr");

        return stream.get();
    }

    return is;

}

