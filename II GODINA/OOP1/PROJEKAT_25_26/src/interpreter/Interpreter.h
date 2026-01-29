#ifndef PROJEKAT2526_INTERPRETER_H
#define PROJEKAT2526_INTERPRETER_H
#include <iostream>
#include "tokenizer/Tokenizer.h"
#include "parser/Parser.h"
#include "error/Error.h"

class Interpreter {
private:
    Tokenizer &tokenizer;
    Parser &parser;
    std::string prompt;

    static bool is_blank(const std::string &string);
public:
    Interpreter(Tokenizer &tokenizer, Parser &parser, std::string prompt = "$");
    void set_prompt(const std::string &new_prompt);

    void run() const;

    static void print_error(const Error &error);
};


#endif //PROJEKAT2526_INTERPRETER_H