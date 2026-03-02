#include "String_Input_Stream.h"

String_Input_Stream::String_Input_Stream(std::string text) : stream(std::move(text)){}

bool String_Input_Stream::read_line(std::string &line) {
    return static_cast<bool>(std::getline(stream, line));
}

bool String_Input_Stream::eof() const {
    return stream.eof();
}
