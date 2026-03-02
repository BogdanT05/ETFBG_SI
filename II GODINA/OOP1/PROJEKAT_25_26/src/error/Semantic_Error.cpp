#include "Semantic_Error.h"

#include <utility>

Semantic_Error::Semantic_Error(std::string message_) : message_(std::move(message_)){}

std::string Semantic_Error::message() const {
    return message_;
}
