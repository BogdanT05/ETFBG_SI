#ifndef PROJEKAT2526_TOKENIZER_H
#define PROJEKAT2526_TOKENIZER_H
#include <vector>
#include "Token.h"

class Tokenizer {
public:
    static std::vector<Token> tokenize(const std::string &s);
    static void string_literal(std::vector<Token> &tokens, const std::string &s, int &i);
    static void pipe(std::vector<Token> &tokens, int &i);
    static void redirect_append(std::vector<Token> &tokens, int &i);
    static void redirect(std::vector<Token> &tokens, Token_type type, std::string value, int &i);
    static void option(std::vector<Token> &tokens, const std::string &s, int &i);
    static void word(std::vector<Token> &tokens, const std::string &s, int &i);
};


#endif //PROJEKAT2526_TOKENIZER_H