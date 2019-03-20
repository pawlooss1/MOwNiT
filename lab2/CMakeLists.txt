cmake_minimum_required(VERSION 3.13)
project(lab2 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab2 main.c matrix_double.c matrix_double.h vector_double.c vector_double.h excercise_double.c excercise_double.h matrix_float.c matrix_float.h vector_float.c vector_float.h exercise_float.c exercise_float.h)

target_link_libraries(lab2 m)