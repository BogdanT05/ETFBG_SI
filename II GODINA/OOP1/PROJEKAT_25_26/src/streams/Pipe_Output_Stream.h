#ifndef PROJEKAT2526_PIPE_OUTPUT_STREAM_H
#define PROJEKAT2526_PIPE_OUTPUT_STREAM_H
#include "Output_Stream.h"
#include "Pipe_Buffer.h"
#include <string>


class Pipe_Output_Stream : public Output_Stream{
private:
    Pipe_Buffer *buffer;
public:
    explicit Pipe_Output_Stream(Pipe_Buffer *buffer);
    void write_line(const std::string &line) override;
    void flush() override;
};


#endif //PROJEKAT2526_PIPE_OUTPUT_STREAM_H