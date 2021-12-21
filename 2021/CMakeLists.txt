cmake_minimum_required(VERSION 3.19)
project(2021)

set(CMAKE_CXX_STANDARD 17)

find_package(BISON REQUIRED)

add_executable(day01 day01.cpp)

bison_target(day2cc day02cc.y ${CMAKE_CURRENT_BINARY_DIR}/day02cc.c)
add_executable(day02 day02.cpp ${CMAKE_CURRENT_BINARY_DIR}/day02cc.c ${CMAKE_CURRENT_BINARY_DIR}/day02cc.h)
target_include_directories(day02 PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

add_executable(day03 day03.cpp)

add_executable(day04 day04.cpp)

add_executable(day05 day05.cpp)

add_executable(day06 day06.cpp day06.input)

add_executable(day07 day07.cpp day07.input)

add_executable(day08_p2 day08.cpp)

add_executable(day09 day09.cpp)

add_executable(day10 day10.cpp)

add_executable(day11 day11.cpp)

add_executable(day12 day12.cpp)

add_executable(day13 day13.cpp)

add_executable(day14 day14.cpp)

add_executable(day15 day15.cpp)

add_executable(day16 day16.cpp)

add_executable(day17 day17.cpp)

add_executable(day18 day18.cpp)

add_executable(day19 day19.cpp)

add_executable(day20 day20.cpp)

add_executable(day21 day21.cpp)