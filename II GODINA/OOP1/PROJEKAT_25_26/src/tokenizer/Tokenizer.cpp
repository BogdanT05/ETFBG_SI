#include "Tokenizer.h"

std::vector<Token> Tokenizer::tokenize(const std::string &s) {
    std::vector<Token> tokens;
    int i = 0;
    while (i < s.length()){
        char current_char = s[i];
        if (std::isspace(static_cast<unsigned char>(current_char))) {
            i++;
            continue;
        }

        if (current_char == '"') {
            int starting_positon = i;
            std::string word;
            i++;

            while (i < s.length() && s[i] != '"')
                word += s[i++];

            if (i == s.length()) throw Lexical_Error(starting_positon, i-starting_positon,
                "Unterminated string literal");
            Token token(Token_type::STRING, word, starting_positon);
            tokens.push_back(token);
            i++;
            continue;
        }

        if (current_char == '|') {
            Token token(Token_type::PIPE, "|", i);
            tokens.push_back(token);
            i++;
            continue;
        }

        if (current_char == '>' && i+1 < s.length() && s[i+1] == '>') {
            Token token(Token_type::REDIRECT_APPEND, ">>", i);
            tokens.push_back(token);
            i+=2;
            continue;
        }

        if (current_char == '>') {
            Token token(Token_type::REDIRECT_OUT, ">", i);
            tokens.push_back(token);
            i++;
            continue;
        }


        if (current_char == '<') {
            Token token(Token_type::REDIRECT_IN, "<", i);
            tokens.push_back(token);
            i++;
            continue;
        }

        if (current_char == '-') {
            int starting_positon = i;
            std::string word;
            Token_type option = Token_type::OPTION;
            bool special_arg = false;
            i++;
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
                while (i < s.length() && !std::isspace(static_cast<unsigned char>(s[i])) && s[i] != '|' && s[i] != '"' && s[i] != '<' && s[i] != '>')
                    word += s[i++];
            }

            if (special_arg)
                option = Token_type::STRING;

            Token token(option, "-"+word, starting_positon);
            tokens.push_back(token);

            continue;
        }

        int starting_positon = i;
        std::string word;

        while (i < s.length() && !std::isspace(static_cast<unsigned char>(s[i])) && s[i] != '|' && s[i] != '"' && s[i] != '<' && s[i] != '>')
            word += s[i++];

        Token token(Token_type::WORD, word, starting_positon);
        tokens.push_back(token);
    }

    return tokens;
}
