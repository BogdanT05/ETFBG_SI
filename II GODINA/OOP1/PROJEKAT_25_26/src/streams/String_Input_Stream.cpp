#include "String_Input_Stream.h"

String_Input_Stream::String_Input_Stream(const std::string& text) : stream(text){}

bool String_Input_Stream::read_line(std::string &line) {
    return static_cast<bool>(std::getline(stream, line));
}

bool String_Input_Stream::eof() const {
    return stream.eof();
}
