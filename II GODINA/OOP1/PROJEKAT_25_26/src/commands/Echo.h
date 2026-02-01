#ifndef PROJEKAT2526_ECHO_H
#define PROJEKAT2526_ECHO_H
#include "Command.h"


class Echo : public Command{
public:
    using Command::Command;
    void execute() override;

    void set_input(Input_Stream *is_) override {is = is_;}
    void set_output(Output_Stream *os_) override {os = os_;}
};


#endif //PROJEKAT2526_ECHO_H