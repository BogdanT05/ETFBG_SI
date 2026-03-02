#ifndef PROJEKAT2526_SYNTAX_ERROR_H
#define PROJEKAT2526_SYNTAX_ERROR_H
#include "Error.h"

class Syntax_Error : public Error{
    int position_;
    int length_;
public:
    explicit Syntax_Error(int position_, int length_=1);
    [[nodiscard]]std::string message() const override;
    [[nodiscard]]int position() const override;
    [[nodiscard]]int length() const override;
};


#endif //PROJEKAT2526_SYNTAX_ERROR_H