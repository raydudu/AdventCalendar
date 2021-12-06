cmake_minimum_required(VERSION 3.19)
project(2021)

set(CMAKE_CXX_STANDARD 17)

find_package(BISON REQUIRED)

add_executable(day1 day1.cpp)

bison_target(day2cc day2cc.y ${CMAKE_CURRENT_BINARY_DIR}/day2cc.c)
add_executable(day2 day2.cpp ${CMAKE_CURRENT_BINARY_DIR}/day2cc.c)
target_include_directories(day2 PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

add_executable(day3 day3.cpp)

add_executable(day4 day4.cpp)

add_executable(day5 day5.cpp)