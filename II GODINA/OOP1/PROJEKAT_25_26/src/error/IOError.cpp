#include "IOError.h"
#include <utility>

IOError::IOError(std::string message_) : Execution_Error(std::move(message_)){}
