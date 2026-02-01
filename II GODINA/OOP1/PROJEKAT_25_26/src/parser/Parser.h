#ifndef PROJEKAT2526_PARSER_H
#define PROJEKAT2526_PARSER_H

#include <memory>
#include "Command.h"
#include "Tokenizer.h"
#include "Execution_Plan.h"

class Parser {
private:
    static std::unique_ptr<Execution_Plan> parse_single_command(const std::vector<Token> &tokens);
    static std::unique_ptr<Execution_Plan> parse_batch(const std::vector<Token> &tokens);

    static std::unique_ptr<Execution_Plan> parse_pipeline(const std::vector<Token> &tokens);
    static std::unique_ptr<Command> parse_command_segment(const std::vector<Token> &tokens);
    static std::unique_ptr<Command> make_command(const std::string &command, const std::vector<std::string> &arguments, const std::vector<std::string> &options);
public:
    std::unique_ptr<Execution_Plan> parse(std::vector<Token> &tokens);
};


#endif //PROJEKAT2526_PARSER_H