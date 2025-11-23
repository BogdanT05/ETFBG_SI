cmake_minimum_required(VERSION 3.10)
project("PRETRAZIVANJE U STABLU")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BinaryTree
        "main.cpp"
        "binary_tree.cpp"
        "binary_tree.h"
        "avl_tree.cpp"
)