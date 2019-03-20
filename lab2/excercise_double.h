//
// Created by pawel on 20.03.19.
//

#ifndef LAB2_EXCERCISE_DOUBLE_H
#define LAB2_EXCERCISE_DOUBLE_H

#include "vector_double.h"
#include "matrix_double.h"

Matrix create_augmented_matrix(Matrix m, Vector v);
Vector gauss(Matrix a);
Vector multiply_matrix_by_vector(Matrix m, Vector v);
Matrix generate_first_matrix(int size);
Matrix generate_second_matrix(int size);
Vector generate_example_vector(int length);

#endif //LAB2_EXCERCISE_DOUBLE_H
