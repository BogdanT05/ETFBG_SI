#include "Console_Input_Stream.h"
#include <iostream>

bool Console_Input_Stream::read_line(std::string &line) {
    if (!std::getline(std::cin, line)) {
        if (std::cin.eof()) {
            std::cin.clear();
        }
        return false;
    }

    if (line.size() > 512)
        line = line.substr(0, 512);

    return true;
}

bool Console_Input_Stream::eof() const {
    return std::cin.eof();
}
