cmake_minimum_required(VERSION 3.10)
project("DZ2")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DZ2
        "asp2dz2p1.cpp"
        "src/Tree234.cpp"
        "src/Tree234.h"
        "src/Process.cpp"
        "src/Process.h"
        src/Scheduler.cpp
        src/Scheduler.h
)