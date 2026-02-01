#ifndef PROJEKAT2526_COMMAND_H
#define PROJEKAT2526_COMMAND_H
#include <iostream>
#include <vector>

#include "Input_Stream.h"
#include "Output_Stream.h"

class Command {
protected:
    std::string name;
    std::vector<std::string> arguments;
    std::vector<std::string> options;

    Input_Stream *is;
    Output_Stream *os;
public:
    Command(std::string name, std::vector<std::string> arguments, std::vector<std::string> options):
        name(std::move(name)), arguments(std::move(arguments)), options(std::move(options)), is(nullptr), os(nullptr)
    {}

    virtual void set_input(Input_Stream *is_) = 0;
    virtual void set_output(Output_Stream *os_) = 0;

    virtual void execute() = 0;
    virtual ~Command() = default;
};


#endif //PROJEKAT2526_COMMAND_H