#include "Lexical_Error.h"
#include <utility>

Lexical_Error::Lexical_Error(int position, int length, std::string message) :
    position_(position),
    length_(length),
    message_(std::move(message))
{}

std::string Lexical_Error::message() const {
    return message_;
}

int Lexical_Error::position() const {
    return position_;
}

int Lexical_Error::length() const {
    return length_;
}
