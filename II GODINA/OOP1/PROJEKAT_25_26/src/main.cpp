#include "CLI.h"

int main() {
    Tokenizer tokenizer;
    Parser parser;

    Interpreter interpreter(tokenizer, parser, "$ ");

    interpreter.run();

    return 0;
}