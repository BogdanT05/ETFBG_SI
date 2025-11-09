cmake_minimum_required(VERSION 3.10)
project("STARI ROKOVI")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(K12017
        "K1 2017/performer.cpp"
        "K1 2017/main.cpp"
        "K1 2017/song.cpp"
        "K1 2017/playlist.cpp"
)