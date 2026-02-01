cmake_minimum_required(VERSION 3.10)
project("Projekat2526")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
        src/*.cpp
)

add_executable(Projekat2526
        ${SOURCES}
        src/CLI.h
        src/streams/Pipe_Buffer.h
        src/error/Unknown_Command_Error.cpp
        src/error/Unknown_Command_Error.h
        src/error/Error.cpp
)

target_include_directories(Projekat2526 PRIVATE
        src
        src/commands
        src/error
        src/execution
        src/interpreter
        src/parser
        src/streams
        src/tokenizer
)