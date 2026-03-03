#include "Command.h"
#include <memory>
#include "File_Input_Stream.h"
#include "String_Input_Stream.h"
#include "Token.h"

// Only true method in command class that is used for resolving input/output streams
// Other commands usually dont override this method
Input_Stream *Command::resolve_input(std::unique_ptr<Input_Stream> &stream) {

    if (!arguments.empty()) {
        if (arguments[0].type == Token_type::STRING){
            stream = std::make_unique<String_Input_Stream>(arguments[0].value);
        }
        else {
            stream = std::make_unique<File_Input_Stream>(arguments[0].value);
        }
        return stream.get();
    }

    return is;
}
