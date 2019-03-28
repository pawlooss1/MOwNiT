//
// Created by pawel on 20.03.19.
//

#ifndef LAB2_EXERCISE_FLOAT_H
#define LAB2_EXERCISE_FLOAT_H

#include "vector_float.h"
#include "matrix_float.h"
#include "banded_matrix_float.h"

Matrix_f create_augmented_matrix_f(Matrix_f m, Vector_f v);
Vector_f gauss_f(Matrix_f a);
Vector_f multiply_matrix_by_vector_f(Matrix_f m, Vector_f v);
Matrix_f generate_first_matrix_f(int size);
Matrix_f generate_second_matrix_f(int size);
BandedMatrix_f *generate_third_matrix_banded_f(int size, float k, float m);
Matrix_f generate_third_matrix_classic_f(int size, float k, float m);
Vector_f generate_example_vector_f(int length);
Vector_f multiply_banded_matrix_by_vector_f(BandedMatrix_f *m, Vector_f v);
Vector_f thomas_f(BandedMatrix_f *matrix);

#endif //LAB2_EXERCISE_FLOAT_H
