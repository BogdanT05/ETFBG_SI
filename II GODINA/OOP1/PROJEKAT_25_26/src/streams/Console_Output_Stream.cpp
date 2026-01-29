#include "Console_Output_Stream.h"

#include <iostream>

void Console_Output_Stream::write_line(const std::string &line) {
    std::cout << line << '\n';
}

void Console_Output_Stream::flush() {
    std::cout.flush();
}

