#ifndef PROJEKAT2526_TOKEN_H
#define PROJEKAT2526_TOKEN_H
#include <string>

enum class Token_type {
    WORD, OPTION, STRING, PIPE, REDIRECT_IN,
    REDIRECT_OUT, REDIRECT_APPEND
};

class Token {
private:
    Token_type type;
    std::string value;
    int position;
public:
    Token(const Token_type type, std::string value, const int position): type(type), value(std::move(value)), position(position) {}

    [[nodiscard]] Token_type get_type() const {return type;}
    [[nodiscard]] std::string get_value() const {return value;}
    [[nodiscard]] int get_position() const {return position;}
};

#endif //PROJEKAT2526_TOKEN_H