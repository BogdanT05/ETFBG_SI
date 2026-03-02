#include "Batch_Command.h"
#include "File_Input_Stream.h"
#include "Interpreter.h"
#include "IOError.h"
#include "Semantic_Error.h"

void Batch::execute(Interpreter &interpreter) {
    std::string filename = arguments[0];
    File_Input_Stream file_stream(filename);

    if (file_stream.eof())
        throw IOError("Cannot open file '"+arguments[0]+"'");

    Output_Stream *old = interpreter.get_output();
    interpreter.set_output(os);

    std::string line;
    while(file_stream.read_line(line)){
        if (line.empty())
            continue;

        interpreter.execute_line(line);
    }

    interpreter.set_output(old);
}

void Batch::validate() {
    if (!options.empty())
        throw Semantic_Error("batch does not accept options");
    if (arguments.size() != 1)
        throw Semantic_Error("batch requires exactly one argument");
}
