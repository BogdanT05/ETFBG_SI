cmake_minimum_required(VERSION 3.10)
project("ZADACI ZA VEZBU")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# prvi program
add_executable(Zadatak1
        "ZADATAK 1/main.cpp"
        "ZADATAK 1/point.cpp"
)

# drugi program
add_executable(Zadatak2
        "ZADATAK 2/main.cpp"
        "ZADATAK 2/angle.cpp"
)

add_executable(Zadatak3
        "ZADATAK 3/main.cpp"
        "ZADATAK 3/queue.cpp"
)

add_executable(Zadatak4
        "ZADATAK 4/cuboid.cpp"
        "ZADATAK 4/main.cpp"
)

add_executable(Zadatak5
        "ZADATAK 5/main.cpp"
        "ZADATAK 5/jmbg.cpp"
        "ZADATAK 5/person.h"
        "ZADATAK 5/directory.cpp"
)

add_executable(Zadatak6
        "ZADATAK 6/main.cpp"
        "ZADATAK 6/Complex.cpp"
        "ZADATAK 6/Complex.h"
        "ZADATAK 6/Array.h"
        "ZADATAK 6/Array.cpp"
        "ZADATAK 6/Iterator.h"
        "ZADATAK 6/Iterator.cpp"
)