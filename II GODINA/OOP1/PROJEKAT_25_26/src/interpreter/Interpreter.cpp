#include "Interpreter.h"
#include <algorithm>
#include <vector>
#include "Token.h"

Interpreter::Interpreter(Tokenizer &tokenizer, Parser &parser, std::string prompt) :
tokenizer(tokenizer),
parser(parser),
prompt(std::move(prompt))
{}

void Interpreter::set_prompt(const std::string& new_prompt) {
    prompt = new_prompt;
}

void Interpreter::run() const {
    while (true) {
        std::string raw_command;
        std::cout << prompt;
        if (!std::getline(std::cin, raw_command)) break;

        if (raw_command.empty() || is_blank(raw_command)) continue;

        try{
            std::vector<Token> tokens = Tokenizer::tokenize(raw_command);
            auto execution_plan = parser.parse(tokens);
            execution_plan->execute();
        }
        catch (const Error &er) {
            print_error(er);
        }
    }
}

void Interpreter::print_error(const Error &error) {
    error.print();
}

bool Interpreter::is_blank(const std::string &string) {
    return std::all_of(string.begin(), string.end(), [](const unsigned char c){return std::isspace(c);});
}
