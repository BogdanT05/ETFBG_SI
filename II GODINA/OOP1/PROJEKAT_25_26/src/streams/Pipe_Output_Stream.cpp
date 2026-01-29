#include "Pipe_Output_Stream.h"

Pipe_Output_Stream::Pipe_Output_Stream(Pipe_Buffer *buffer): buffer(buffer) {}

void Pipe_Output_Stream::write_line(const std::string &line) {
    buffer->data_buffer.push_back(line);
}

void Pipe_Output_Stream::flush() {

}

