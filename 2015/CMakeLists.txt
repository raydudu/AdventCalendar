cmake_minimum_required(VERSION 3.21)
project(2015)

set(CMAKE_CXX_STANDARD 17)

add_executable(bmp_test BMP_test.cpp BMP.h)

add_executable(day1 day1.cpp)

add_executable(day2 day2.cpp)
add_executable(day3 day3.cpp)

find_package(OpenSSL REQUIRED)
add_executable(day4 day4.cpp)
target_link_libraries(day4 PRIVATE OpenSSL::Crypto)

add_executable(day5 day5.cpp)
add_executable(day6 day6.cpp)