cmake_minimum_required(VERSION 3.30)
project(testThree C)

set(CMAKE_C_STANDARD 11)

add_executable(main main.c)
add_executable(fszip fszip.c)
add_executable(fsunzip fsunzip.c)

