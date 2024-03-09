cmake_minimum_required(VERSION 3.26)
project(Git_project C)

set(CMAKE_C_STANDARD 11)

add_executable(Git_project main.c
        libs/data_structures/vector/vector.h
        libs/data_structures/vector/vector.c
        libs/data_structures/vector/vectorVoid.h
        libs/data_structures/vector/vectorVoid.c
        libs/data_structures/matrix/matrix.h
        libs/data_structures/matrix/matrix.c
)
