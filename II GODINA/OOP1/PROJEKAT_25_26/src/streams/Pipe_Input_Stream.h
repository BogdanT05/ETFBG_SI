#ifndef PROJEKAT2526_PIPE_INPUT_STREAM_H
#define PROJEKAT2526_PIPE_INPUT_STREAM_H
#include "Input_Stream.h"
#include "Pipe_Buffer.h"


class Pipe_Input_Stream : public Input_Stream{
private:
    Pipe_Buffer *buffer;
    std::size_t read_index = 0;
public:
    explicit Pipe_Input_Stream(Pipe_Buffer *buffer);
    bool read_line(std::string &line) override;
    [[nodiscard]] bool eof() const override;
};


#endif //PROJEKAT2526_PIPE_INPUT_STREAM_H