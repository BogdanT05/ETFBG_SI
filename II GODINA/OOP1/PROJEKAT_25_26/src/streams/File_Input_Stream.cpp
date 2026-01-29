#include "File_Input_Stream.h"

#include "IOError.h"

File_Input_Stream::File_Input_Stream(const std::string& filename){
    file.open(filename);
    if (!file.is_open()){}
        //throw IOError("Cannot open input file", filename);
}

bool File_Input_Stream::read_line(std::string &line) {
    return static_cast<bool>(std::getline(file, line));
}

bool File_Input_Stream::eof() const {
    return file.eof();
}
