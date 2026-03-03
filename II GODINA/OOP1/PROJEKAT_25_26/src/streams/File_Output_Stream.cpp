#include "File_Output_Stream.h"
#include "IOError.h"

File_Output_Stream::File_Output_Stream(const std::string &filename, bool append){
    if (append)
        file.open(filename, std::ios::app);
    else
        file.open(filename, std::ios::out);

    if (!file.is_open())
         throw IOError("Cannot open output file '" + filename +"'");
}

void File_Output_Stream::write_line(const std::string &line) {
    file << line;
    file.flush();
}

// flush forces content in buffer to memory/files
// Necessary for immediate changes in file system.
void File_Output_Stream::flush() {
    file.flush();
}
