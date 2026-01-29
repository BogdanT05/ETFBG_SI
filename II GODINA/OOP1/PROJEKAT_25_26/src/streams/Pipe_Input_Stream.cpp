#include "Pipe_Input_Stream.h"

Pipe_Input_Stream::Pipe_Input_Stream(Pipe_Buffer *buffer) : buffer(buffer){}

bool Pipe_Input_Stream::read_line(std::string &line) {
    if (read_index >= buffer->data_buffer.size())
        return false;

    line = buffer->data_buffer[read_index++];
    return true;
}

bool Pipe_Input_Stream::eof() const {
    return read_index >= buffer->data_buffer.size();
}
