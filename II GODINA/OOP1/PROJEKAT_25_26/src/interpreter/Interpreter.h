#ifndef PROJEKAT2526_INTERPRETER_H
#define PROJEKAT2526_INTERPRETER_H
#include <iostream>

#include "Console_Output_Stream.h"
#include "tokenizer/Tokenizer.h"
#include "parser/Parser.h"
#include "error/Error.h"

class Interpreter {
private:
    Tokenizer &tokenizer;
    Parser &parser;
    std::string prompt;
    Output_Stream *output;

    static bool is_blank(const std::string &string);
public:
    Interpreter(Tokenizer &tokenizer, Parser &parser, std::string prompt = "$");
    ~Interpreter();
    void set_prompt(const std::string &new_prompt);
    void execute_line(const std::string &line);
    void run();
    static void print_error(const Error &error);

    [[nodiscard]] Output_Stream* get_output() const;
    void set_output(Output_Stream* out);
};


#endif //PROJEKAT2526_INTERPRETER_H