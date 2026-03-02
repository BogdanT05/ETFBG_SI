#ifndef PROJEKAT2526_COMMAND_H
#define PROJEKAT2526_COMMAND_H
#include <vector>
#include <memory>
#include "Input_Stream.h"
#include "Output_Stream.h"
#include "Token.h"

class Interpreter;

struct Argument {
    std::string value;
    Token_type type;
};

class Command {
protected:
    std::string name;
    std::vector<Argument> arguments;
    std::vector<std::string> options;

    Input_Stream *is;
    Output_Stream *os;

    Input_Stream* resolve_input(std::unique_ptr<Input_Stream> &stream);
public:
    Command(std::string name, std::vector<Argument> arguments, std::vector<std::string> options):
        name(std::move(name)), arguments(std::move(arguments)), options(std::move(options)), is(nullptr), os(nullptr)
    {}

    virtual void set_input(Input_Stream *is_) = 0;
    virtual void set_output(Output_Stream *os_) = 0;
    virtual void validate() = 0;

    virtual void execute(Interpreter &interpreter) = 0;
    virtual ~Command() = default;
};


#endif //PROJEKAT2526_COMMAND_H