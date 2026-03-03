#ifndef PROJEKAT2526_STRING_INPUT_STREAM_H
#define PROJEKAT2526_STRING_INPUT_STREAM_H
#include <sstream>
#include "Input_Stream.h"

// Class that is responsible for reading from string stream

class String_Input_Stream : public Input_Stream{
private:
    std::istringstream stream;
public:
    explicit String_Input_Stream(const std::string& text);
    bool read_line(std::string &line) override;
    bool eof() const override;
};


#endif //PROJEKAT2526_STRING_INPUT_STREAM_H