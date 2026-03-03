#ifndef PROJEKAT2526_CONSOLE_INPUT_STREAM_H
#define PROJEKAT2526_CONSOLE_INPUT_STREAM_H
#include <string>
#include "Input_Stream.h"

// Class responsible for reading from command line

class Console_Input_Stream : public Input_Stream {
public:
    bool read_line(std::string &line) override;
    [[nodiscard]] bool eof() const override;
    [[nodiscard]] bool is_console() const override {return true;}
};


#endif //PROJEKAT2526_CONSOLE_INPUT_STREAM_H