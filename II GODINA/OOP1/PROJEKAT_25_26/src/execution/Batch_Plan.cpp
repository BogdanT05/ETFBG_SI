#include "Batch_Plan.h"

#include <algorithm>

#include "Error.h"
#include "Parser.h"
#include "Tokenizer.h"


Batch_Plan::Batch_Plan(Input_Stream *stream ,Tokenizer &tokenizer, Parser &parser) : file(stream), tokenizer(tokenizer), parser(parser){}

void Batch_Plan::execute() {
    std::string line;
    while (file->read_line(line)) {
        if (line.empty() || is_blank(line)) continue;

        try{
            std::vector<Token> tokens = Tokenizer::tokenize(line);
            const auto execution_plan = parser.parse(tokens);
            execution_plan->execute();
        }
        catch (const Error &er) {
            print_error(er);
        }
    }
}

void Batch_Plan::print_error(const Error &error) {
    error.print();
}

bool Batch_Plan::is_blank(const std::string &string) {
    return std::all_of(string.begin(), string.end(), [](const unsigned char c){return std::isspace(c);});
}
