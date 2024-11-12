cmake_minimum_required(VERSION 3.29)
project(Lab5 C)

set(CMAKE_C_STANDARD 23)

add_executable(Lab5 main.c
        tic_tac_toe.c
        tic_tac_toe.h)
