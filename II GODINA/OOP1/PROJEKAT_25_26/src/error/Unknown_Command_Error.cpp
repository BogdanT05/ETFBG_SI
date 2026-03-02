#include "Unknown_Command_Error.h"

Unknown_Command_Error::Unknown_Command_Error(std::string &command, int position_) : Semantic_Error(""),
command(std::move(command)), position_(position_)
{}

std::string Unknown_Command_Error::message() const {
    return "Unknown Command: " + command;
}

int Unknown_Command_Error::position() const {
    return position_;
}

int Unknown_Command_Error::length() const {
    return static_cast<int>(command.length());
}
