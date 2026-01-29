#include "Console_Input_Stream.h"
#include <iostream>

bool Console_Input_Stream::read_line(std::string &line) {
    return static_cast<bool>(std::getline(std::cin, line));
}

bool Console_Input_Stream::eof() const {
    return std::cin.eof();
}
