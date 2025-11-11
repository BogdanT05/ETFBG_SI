cmake_minimum_required(VERSION 3.10)
project("PRETRAZIVANJE U LISTI")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PretLista
    "main.cpp"
    "linked_list.cpp"
    "sorted_list.cpp"
)