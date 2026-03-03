#include "Parser.h"
#include "Batch_Command.h"
#include "Batch_Plan.h"
#include "Command.h"
#include "Console_Input_Stream.h"
#include "Console_Output_Stream.h"
#include "Date_Command.h"
#include "Echo_Command.h"
#include "File_Input_Stream.h"
#include "File_Output_Stream.h"
#include "Head_Command.h"
#include "Input_Stream.h"
#include "Output_Stream.h"
#include "Pipe_Line_Plan.h"
#include "Prompt_Command.h"
#include "Rm_Command.h"
#include "Single_Command_Plan.h"
#include "Syntax_Error.h"
#include "Touch_Command.h"
#include "Tr_Command.h"
#include "Truncate_Command.h"
#include "Unknown_Command_Error.h"
#include "Wc_Command.h"
#include "Execution_Plan.h"
#include "Time_Command.h"

std::unique_ptr<Execution_Plan> Parser::parse_single_command(const std::vector<Token> &tokens) {
    auto command = parse_command_segment(tokens);
    auto single_command_plan = std::make_unique<Single_Command_Plan>(std::move(command));
    return single_command_plan;
}

std::unique_ptr<Execution_Plan> Parser::parse_batch(const std::vector<Token> &tokens) {
    if (tokens.empty()) throw Syntax_Error(-1);
    if (tokens[0].get_value() != "batch") throw Syntax_Error(tokens[0].get_position());

    std::string filename;
    bool script_seen = false;
    bool output_seen = false;

    std::unique_ptr<Output_Stream> output_stream = std::make_unique<Console_Output_Stream>();

    for (std::size_t i = 1; i < tokens.size(); i++) {
        if (tokens[i].get_type() == Token_type::PIPE) throw Syntax_Error(tokens[i].get_position());
        if (tokens[i].get_type() == Token_type::REDIRECT_IN) throw Syntax_Error(tokens[i].get_position());
        if (tokens[i].get_type() == Token_type::STRING || tokens[i].get_type() == Token_type::WORD) {
            if (!script_seen) {
                filename = tokens[i].get_value();
                script_seen = true;
            }
            else throw Syntax_Error(tokens[i].get_position());
        }
        else if (tokens[i].get_type() == Token_type::REDIRECT_OUT) {
            if (!output_seen && i + 1 < tokens.size() &&
                (tokens[i+1].get_type() == Token_type::STRING || tokens[i+1].get_type() == Token_type::WORD)) {
                output_stream = std::make_unique<File_Output_Stream>(tokens[++i].get_value(), false);
                output_seen = true;
            }
            else throw Syntax_Error(tokens[i].get_position());
        }
        else if (tokens[i].get_type() == Token_type::REDIRECT_APPEND) {
            if (!output_seen && i + 1 < tokens.size() &&
                (tokens[i+1].get_type() == Token_type::STRING || tokens[i+1].get_type() == Token_type::WORD)) {
                output_stream = std::make_unique<File_Output_Stream>(tokens[++i].get_value(), true);
                output_seen = true;
            }
            else throw Syntax_Error(tokens[i].get_position());
        }
    }

    if (!script_seen) throw Syntax_Error(tokens[0].get_position());
    std::unique_ptr<Input_Stream> script = std::make_unique<File_Input_Stream>(filename);

    return std::make_unique<Batch_Plan>(script.release(), output_stream.release());
}

std::unique_ptr<Execution_Plan> Parser::parse_pipeline(const std::vector<Token> &tokens) {
    std::vector<std::unique_ptr<Command>> commands;
    std::vector<Token> segment;
    std::vector<std::vector<Token>> segments;

    if (tokens.empty())
        throw Syntax_Error(0);

    if (tokens.back().get_type() == Token_type::PIPE)
        throw Syntax_Error(tokens.back().get_position());

    for (const auto & token : tokens) {
        if (token.get_type() != Token_type::PIPE)
            segment.push_back(token);
        else {
            if (segment.empty()) throw Syntax_Error(token.get_position());
            segments.push_back(segment);
            segment.clear();
        }
    }
    if (!segment.empty()) {
        segments.push_back(segment);
    }

    for (std::size_t i = 0; i < segments.size(); i++) {
        for (const auto &token:segments[i]) {
            if (i == 0 &&
                (token.get_type() == Token_type::REDIRECT_OUT ||
                token.get_type() == Token_type::REDIRECT_APPEND))
                throw Syntax_Error(token.get_position());

            if (i == segments.size() - 1 && token.get_type() == Token_type::REDIRECT_IN)
                throw Syntax_Error(token.get_position());

            if (i > 0 && i < segments.size()-1 &&
                (token.get_type() == Token_type::REDIRECT_OUT ||
                token.get_type() == Token_type::REDIRECT_APPEND ||
                token.get_type() == Token_type::REDIRECT_IN))
                throw Syntax_Error(token.get_position());
        }
    }

    commands.reserve(segments.size());
    for (const auto& segment_ : segments) {
        commands.push_back(parse_command_segment(segment_));
    }

    return std::make_unique<Pipe_Line_Plan>(std::move(commands));
}

std::unique_ptr<Command> Parser::parse_command_segment(const std::vector<Token> &tokens) {
    if (tokens.empty())
        throw Syntax_Error(0);

    if (tokens[0].get_type() != Token_type::WORD)
        throw Syntax_Error(tokens[0].get_position());

    std::string command_name = tokens[0].get_value();

    std::vector<std::string> options;
    std::vector<Argument> arguments;
    std::unique_ptr<Input_Stream> command_input = nullptr;
    std::unique_ptr<Output_Stream> command_output = nullptr;

    bool seen_redirection_in = false;
    bool seen_redirection_out = false;

    bool has_argument = false;
    int redirect_in_position = -1;

    for (std::size_t i = 1; i < tokens.size(); i++) {

        if (tokens[i].get_type() == Token_type::OPTION) options.push_back(tokens[i].get_value());
        else if (tokens[i].get_type() == Token_type::STRING || tokens[i].get_type() == Token_type::WORD) {
            arguments.push_back(Argument{tokens[i].get_value(), tokens[i].get_type()});
            has_argument = true;
        }
        else if (tokens[i].get_type() == Token_type::REDIRECT_IN) {
            if (i+1 < tokens.size() && (tokens[i+1].get_type() == Token_type::STRING || tokens[i+1].get_type() == Token_type::WORD)) {
                if (!seen_redirection_in) {
                    redirect_in_position = tokens[i].get_position();
                    command_input = std::make_unique<File_Input_Stream>(tokens[++i].get_value());
                    seen_redirection_in = true;
                }
                else throw Syntax_Error(tokens[i].get_position());
            }
            else throw Syntax_Error(tokens[i].get_position());

        }
        else if (tokens[i].get_type() == Token_type::REDIRECT_OUT) {
            if (i+1 < tokens.size() && (tokens[i+1].get_type() == Token_type::STRING || tokens[i+1].get_type() == Token_type::WORD)) {
                if (!seen_redirection_out) {
                    command_output = std::make_unique<File_Output_Stream>(tokens[++i].get_value(), false);
                    seen_redirection_out = true;
                }
                else throw Syntax_Error(tokens[i].get_position());
            }

            else throw Syntax_Error(tokens[i].get_position());
        }
        else if(tokens[i].get_type() == Token_type::REDIRECT_APPEND){
            if (i+1 < tokens.size() && (tokens[i+1].get_type() == Token_type::STRING || tokens[i+1].get_type() == Token_type::WORD)) {
                if (!seen_redirection_out) {
                    command_output = std::make_unique<File_Output_Stream>(tokens[++i].get_value(), true);
                    seen_redirection_out = true;
                }
                else throw Syntax_Error(tokens[i].get_position());
            }

            else throw Syntax_Error(tokens[i].get_position());
        }
    }
  
    if (!seen_redirection_in) {
        command_input = std::make_unique<Console_Input_Stream>();
    }

    if (has_argument && seen_redirection_in)
        throw Syntax_Error(redirect_in_position);

    auto command = make_command(command_name, arguments, options);
    if (!command) throw Unknown_Command_Error(command_name, tokens[0].get_position());

    command->validate();
    command->set_input(command_input.release());
    command->set_output(command_output.release());

    return command;
}

std::unique_ptr<Command> Parser::make_command(const std::string &command,const std::vector<Argument> &arguments,
    const std::vector<std::string> &options) {

    if (command == "batch") return std::unique_ptr<Command>(new Batch(command, arguments, options));
    if (command == "date") return std::unique_ptr<Command>(new Date(command, arguments, options));
    if (command == "echo") return std::unique_ptr<Command>(new Echo(command, arguments, options));
    if (command == "head") return std::unique_ptr<Command>(new Head(command, arguments, options));
    if (command == "prompt") return std::unique_ptr<Command>(new Prompt(command, arguments, options));
    if (command == "rm") return std::unique_ptr<Command>(new Rm(command, arguments, options));
    if (command == "time") return std::unique_ptr<Command>(new Time(command, arguments, options));
    if (command == "touch") return std::unique_ptr<Command>(new Touch(command, arguments, options));
    if (command == "tr") return std::unique_ptr<Command>(new Tr(command, arguments, options));
    if (command == "truncate") return std::unique_ptr<Command>(new Truncate(command, arguments, options));
    if (command == "wc") return std::unique_ptr<Command>(new Wc(command, arguments, options));

    return nullptr;
}

std::unique_ptr<Execution_Plan> Parser::parse(const std::vector<Token> &tokens) {
    if (tokens.empty()) throw Syntax_Error(0);

    for (const auto& token : tokens) {
        if (token.get_type() == Token_type::PIPE)
            return parse_pipeline(tokens);
    }

    if (tokens[0].get_type() == Token_type::WORD && tokens[0].get_value() == "batch")
        return parse_batch(tokens);

    return parse_single_command(tokens);
}
