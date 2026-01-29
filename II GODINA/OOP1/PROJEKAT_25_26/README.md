# CLI Interpreter - Projekat OOP1 2025/2026
## Overview
This project implements a simplified Command Line Interpreter written in C++.
The system supports command execution, input/output redirection, pipelines, and batch processing.
This project is designed with strong object-oriented decomposition.

## Architecture
The system is divided into clearly separated layers:
- Tokenization (lexical analysis)
- Parsing (syntax and semantic analysis)
- Execution planning
- Command execution
- Stream abstraction
- Error handling

## Main components
### Interpreter
Responsible for the main program loop:
- Displays the prompt
- Reads command lines
- Call on tokenizer and parser
- Executes the generated execution plan
- Handles errors and continues execution

### Tokenizer
Converts raw command line in string into sequence of tokens.
Detects lexical errors.

### Parser
Converts tokens from tokenizer and constructs execution plan.
Detects syntax and semantic errors.

### Execution Plan
Execution plan represents executable command structures:
- Single command plan - executes single command
- Pipeline plan - executes a commands connected by pipes
- Batch plan - executes commands from a file

### Commands
Each command is implemented as derived class from abstract Command base class.
Supported commands:
echo, time, date, wc, touch, rm, truncate, tr, head, prompt, batch.

### Streams
Input and output are abstracted via stream interfaces:
- Console streams
- File streams
- Pipe streams

### Error Handling
All errors derive from a common Error base class:
- Lexical error
- Syntax error
- Semantic error
- Execution error
- IOError

Errors are thrown at the layer where they occur and handled by interpreter
## Build
This project uses CMake and requires a C++17 compatible compiler.
