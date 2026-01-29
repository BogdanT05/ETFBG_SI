#ifndef PROJEKAT2526_FILE_OUTPUT_STREAM_H
#define PROJEKAT2526_FILE_OUTPUT_STREAM_H
#include <fstream>

#include "Output_Stream.h"


class File_Output_Stream : public Output_Stream{
private:
    std::ofstream file;
public:
    explicit File_Output_Stream(const std::string& filename, bool append);
    void write_line(const std::string& line) override;
    void flush() override;
};


#endif //PROJEKAT2526_FILE_OUTPUT_STREAM_H