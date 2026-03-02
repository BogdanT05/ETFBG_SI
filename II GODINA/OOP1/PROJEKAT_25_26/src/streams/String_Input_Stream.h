#ifndef PROJEKAT2526_STRING_INPUT_STREAM_H
#define PROJEKAT2526_STRING_INPUT_STREAM_H
#include <sstream>
#include "Input_Stream.h"


class String_Input_Stream : public Input_Stream{
private:
    std::istringstream stream;
public:
    explicit String_Input_Stream(std::string text);
    bool read_line(std::string &line) override;
    bool eof() const override;
};


#endif //PROJEKAT2526_STRING_INPUT_STREAM_H