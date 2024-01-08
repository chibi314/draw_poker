cmake_minimum_required(VERSION 3.1)
project (draw_poker)

add_definitions(-std=c++17)
set(CMAKE_CXX_FLAGS "-O3")

include_directories(./src)

find_package(OpenMP REQUIRED)
if(OpenMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_executable(main ./src/main.cpp)

add_executable(openmp_test ./src/openmp_test.cpp)
