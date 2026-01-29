#ifndef PROJEKAT2526_TOKENIZER_H
#define PROJEKAT2526_TOKENIZER_H
#include <vector>
#include "Lexical_Error.h"
#include "Token.h"

class Tokenizer {
public:
    static std::vector<Token> tokenize(const std::string &s);
};


#endif //PROJEKAT2526_TOKENIZER_H