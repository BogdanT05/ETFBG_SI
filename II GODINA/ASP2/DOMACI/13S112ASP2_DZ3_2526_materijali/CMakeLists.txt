cmake_minimum_required(VERSION 3.10)
project("ASP DZ3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ASPDZ3
        main.cpp
        image.h
        image_processor.h
        sorting.h
        utils.h
        Maja_Heuristic.h
        Marko_Heuristic.cpp
        Maja_Heuristic.cpp
        Marko_Heuristic.h
        Sort.h
        Sort.cpp
)

