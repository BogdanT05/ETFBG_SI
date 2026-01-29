#ifndef PROJEKAT2526_CONSOLE_OUTPUT_STREAM_H
#define PROJEKAT2526_CONSOLE_OUTPUT_STREAM_H
#include <string>

#include "Output_Stream.h"


class Console_Output_Stream : public Output_Stream{
public:
    void write_line(const std::string &line) override;
    void flush() override;
};


#endif //PROJEKAT2526_CONSOLE_OUTPUT_STREAM_H