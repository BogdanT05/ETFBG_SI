#include "Execution_Error.h"

Execution_Error::Execution_Error(std::string &message_) : message_(std::move(message_)){}

std::string Execution_Error::message() const {
    return message_;
}
