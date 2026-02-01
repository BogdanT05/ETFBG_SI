#ifndef PROJEKAT2526_BATCH_PLAN_H
#define PROJEKAT2526_BATCH_PLAN_H
#include "Error.h"
#include "Execution_Plan.h"
#include "Input_Stream.h"
#include "Interpreter.h"
#include "Parser.h"
#include "Tokenizer.h"


class Batch_Plan : public Execution_Plan{
private:
    Input_Stream *file;
    Output_Stream *output_stream;
    static bool is_blank(const std::string &string);
public:
    Batch_Plan(Input_Stream *stream, Output_Stream *output_stream);
    void execute(Interpreter &interpreter) override;
    static void print_error(const Error &error);
};


#endif //PROJEKAT2526_BATCH_PLAN_H