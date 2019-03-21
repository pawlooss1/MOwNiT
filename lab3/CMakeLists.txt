cmake_minimum_required(VERSION 3.13)
project(lab3 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab3 main.c double/matrix_double.c double/matrix_double.h double/vector_double.c double/vector_double.h double/excercise_double.c double/excercise_double.h float/matrix_float.c float/matrix_float.h float/vector_float.c float/vector_float.h float/exercise_float.c float/exercise_float.h double/banded_matrix_double.c double/banded_matrix_double.h float/banded_matrix_float.c float/banded_matrix_float.h)

target_link_libraries(lab3 m)