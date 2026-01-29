#ifndef PROJEKAT2526_INPUT_STREAM_H
#define PROJEKAT2526_INPUT_STREAM_H


class Input_Stream {
public:
    virtual bool read_line(std::string &line) = 0;
    virtual bool eof() = 0;
    virtual ~Input_Stream() = default;
};


#endif //PROJEKAT2526_INPUT_STREAM_H