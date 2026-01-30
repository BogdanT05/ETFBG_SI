#ifndef PROJEKAT2526_BATCH_PLAN_H
#define PROJEKAT2526_BATCH_PLAN_H
#include "Error.h"
#include "Execution_Plan.h"
#include "Input_Stream.h"
#include "Parser.h"
#include "Tokenizer.h"


class Batch_Plan : public Execution_Plan{
private:
    Input_Stream *file;
    Tokenizer &tokenizer;
    Parser &parser;
    static bool is_blank(const std::string &string);
public:
    explicit Batch_Plan(Input_Stream *stream, Tokenizer &tokenizer, Parser &parser);
    void execute() override;
    static void print_error(const Error &error);
};


#endif //PROJEKAT2526_BATCH_PLAN_H