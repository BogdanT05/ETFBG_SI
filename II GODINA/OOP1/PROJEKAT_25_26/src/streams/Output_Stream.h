#ifndef PROJEKAT2526_OUTPUT_STREAM_H
#define PROJEKAT2526_OUTPUT_STREAM_H
#include <string>

class Output_Stream {
public:
    virtual void write_line(const std::string &line) = 0;
    virtual void flush() = 0;

    virtual ~Output_Stream() = default;
};


#endif //PROJEKAT2526_OUTPUT_STREAM_H