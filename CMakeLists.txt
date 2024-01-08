cmake_minimum_required(VERSION 3.1)
project (draw_poker)

add_definitions(-std=c++17)
set(CMAKE_CXX_FLAGS "-O3")

include_directories(./src)

add_executable(main ./src/main.cpp ./src/playing_card.hpp)
