#include "Syntax_Error.h"

Syntax_Error::Syntax_Error(int position_, int length_) : position_(position_), length_(length_){}

int Syntax_Error::position() const {
    return position_;
}

int Syntax_Error::length() const {
    return length_;
}

std::string Syntax_Error::message() const {
    return "Syntax Error";
}
