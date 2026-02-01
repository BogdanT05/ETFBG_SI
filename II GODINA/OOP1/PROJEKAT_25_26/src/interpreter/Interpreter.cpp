#include "Interpreter.h"
#include <algorithm>
#include <vector>
#include "Token.h"

Interpreter::Interpreter(Tokenizer &tokenizer, Parser &parser, std::string prompt) :
tokenizer(tokenizer),
parser(parser),
prompt(std::move(prompt)),
output(new Console_Output_Stream())
{}

Interpreter::~Interpreter() {
    delete output;
}

void Interpreter::set_prompt(const std::string& new_prompt) {
    prompt = new_prompt;
}

void Interpreter::execute_line(const std::string &line) {
    try {
        auto tokens = tokenizer.tokenize(line);
        auto execution_plan = parser.parse(tokens);
        execution_plan->execute(*this);
    }
    catch (const Error &er) {
        print_error(er);
    }
}

void Interpreter::run(){
    while (true) {
        std::string raw_command;
        std::cout << prompt;

        if (!std::getline(std::cin, raw_command))
            break;

        if (raw_command.empty() || is_blank(raw_command))
            continue;

        execute_line(raw_command);
    }
}

void Interpreter::print_error(const Error &error) {
    error.print();
}

Output_Stream * Interpreter::get_output() const {
    return output;
}

void Interpreter::set_output(Output_Stream *out) {
    output = out;
}

bool Interpreter::is_blank(const std::string &string) {
    return std::all_of(string.begin(), string.end(), [](const unsigned char c){return std::isspace(c);});
}
