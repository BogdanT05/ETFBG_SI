#ifndef PROJEKAT2526_CLI_H
#define PROJEKAT2526_CLI_H

// Tokenizer
#include "tokenizer/Token.h"
#include "tokenizer/Tokenizer.h"

// Parser
#include "parser/Parser.h"

// Execution plan
#include "execution/Execution_Plan.h"
#include "execution/Single_Command_Plan.h"
#include "execution/Pipe_Line_Plan.h"
#include "execution/Batch_Plan.h"

// Interpreter
#include "interpreter/Interpreter.h"

// Komande
#include "commands/Command.h"
#include "commands/Echo.h"
#include "commands/Time.h"
#include "commands/Date.h"
#include "commands/Wc.h"
#include "commands/Touch.h"
#include "commands/Prompt.h"
#include "commands/Rm.h"
#include "commands/Truncate.h"
#include "commands/Tr.h"
#include "commands/Head.h"
#include "commands/Batch.h"

// Strimovi
#include "streams/Input_Stream.h"
#include "streams/Output_Stream.h"

#include "streams/Console_Input_Stream.h"
#include "streams/Console_Output_Stream.h"

#include "streams/File_Input_Stream.h"
#include "streams/File_Output_Stream.h"

#include "streams/Pipe_Input_Stream.h"
#include "streams/Pipe_Output_Stream.h"

// Error
#include "error/Error.h"
#include "error/Lexical_Error.h"
#include "error/Syntax_Error.h"
#include "error/Semantic_Error.h"
#include "error/Execution_Error.h"
#include "error/IOError.h"

#endif //PROJEKAT2526_CLI_H