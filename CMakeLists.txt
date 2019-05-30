cmake_minimum_required(VERSION 3.14)
project(pushBox)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-lncursesw")

add_executable(test ncursesTest/main.cpp)
add_executable(pushBox main.cpp)