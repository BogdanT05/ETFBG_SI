#ifndef PROJEKAT2526_FILE_INPUT_STREAM_H
#define PROJEKAT2526_FILE_INPUT_STREAM_H
#include <fstream>

#include "Input_Stream.h"

class File_Input_Stream : public Input_Stream{
private:
    std::ifstream file;
public:
    explicit File_Input_Stream(const std::string& filename);
    bool read_line(std::string &line) override;
    bool eof() const override;
};


#endif //PROJEKAT2526_FILE_INPUT_STREAM_H