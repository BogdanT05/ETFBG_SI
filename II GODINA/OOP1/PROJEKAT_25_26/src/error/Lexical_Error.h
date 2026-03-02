#ifndef PROJEKAT2526_LEXICAL_ERROR_H
#define PROJEKAT2526_LEXICAL_ERROR_H
#include "Error.h"


class Lexical_Error : public Error{
private:
    int position_;
    int length_;
    std::string message_;
public:

    Lexical_Error(int position, int length, std::string message);
    [[nodiscard]] std::string message() const override;
    [[nodiscard]] int position() const override;
    [[nodiscard]] int length() const override;

};


#endif //PROJEKAT2526_LEXICAL_ERROR_H