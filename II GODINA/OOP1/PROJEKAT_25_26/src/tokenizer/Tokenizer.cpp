#include "Tokenizer.h"
#include <utility>
#include "Lexical_Error.h"

std::vector<Token> Tokenizer::tokenize(const std::string &s) {
    std::vector<Token> tokens;
    int i = 0;
    // Different characters lead to their respective token types
    while (i < s.length()){
        char current_char = s[i];
        if (std::isspace(static_cast<unsigned char>(current_char)))
            i++;
        else if (current_char == '"')
            string_literal(tokens, s, i);
        else if (current_char == '|')
            pipe(tokens, i);
        else if (current_char == '>' && i+1 < s.length() && s[i+1] == '>')
            redirect_append(tokens, i);
        else if (current_char == '>')
            redirect(tokens, Token_type::REDIRECT_OUT, ">", i);
        else if (current_char == '<')
            redirect(tokens, Token_type::REDIRECT_IN, "<", i);
        else if (current_char == '-')
            option(tokens, s, i);
        else
            word(tokens, s, i);
    }

    return tokens;
}

void Tokenizer::string_literal(std::vector<Token> &tokens, const std::string &s, int &i) {
    int starting_positon = i;
    std::string word;
    i++;

    while (i < s.length() && s[i] != '"')
        word += s[i++];

    // If closing quotation marks are missing
    if (i == s.length()) throw Lexical_Error(starting_positon, i-starting_positon,
        "Unterminated string literal");
    Token token(Token_type::STRING, word, starting_positon);
    tokens.push_back(token);
    i++;
}

void Tokenizer::pipe(std::vector<Token> &tokens, int &i) {
    Token token(Token_type::PIPE, "|", i);
    tokens.push_back(token);
    i++;
}

void Tokenizer::redirect_append(std::vector<Token> &tokens, int &i) {
    Token token(Token_type::REDIRECT_APPEND, ">>", i);
    tokens.push_back(token);
    // >> takes 2 spaces so we skip 2 characters'][=[;p-
    i+=2;
}

void Tokenizer::redirect(std::vector<Token> &tokens, Token_type type,std::string value, int &i) {
    Token token(type, std::move(value), i);
    tokens.push_back(token);
    i++;
}

void Tokenizer::option(std::vector<Token> &tokens, const std::string &s, int &i) {
    int starting_positon = i;
    std::string word;
    Token_type option = Token_type::OPTION;

    bool special_arg = false;
    i++;
    // For command tr argument has both - and " " so here its recognized with bool special arg
    if (i < s.length() && s[i] == '"') {
        word += '"';
        i++;
        while (i < s.length() && s[i] != '"')
            word += s[i++];

        if (i == s.length())
            throw Lexical_Error(starting_positon, i-starting_positon, "Unterminated string in option");
        word += '"';
        i++;
        special_arg = true;
    }
    else {
        // regular option must end on either blank, |, ", < or >
        while (i < s.length() && !std::isspace(static_cast<unsigned char>(s[i])) && s[i] != '|' && s[i] != '"' && s[i] != '<' && s[i] != '>')
            word += s[i++];
    }

    if (special_arg)
        option = Token_type::STRING;

    // We keep '-' for validation later on
    Token token(option, "-"+word, starting_positon);
    tokens.push_back(token);
}

void Tokenizer::word(std::vector<Token> &tokens, const std::string &s, int &i) {
    int starting_positon = i;
    std::string word;

    while (i < s.length() && !std::isspace(static_cast<unsigned char>(s[i])) && s[i] != '|' && s[i] != '"' && s[i] != '<' && s[i] != '>')
        word += s[i++];

    Token token(Token_type::WORD, word, starting_positon);
    tokens.push_back(token);
}
