//
// Created by pawel on 20.03.19.
//

#ifndef LAB2_EXCERCISE_DOUBLE_H
#define LAB2_EXCERCISE_DOUBLE_H

#include "vector_double.h"
#include "matrix_double.h"
#include "banded_matrix_double.h"

Matrix create_augmented_matrix(Matrix m, Vector v);
Vector gauss(Matrix a);
Vector multiply_matrix_by_vector(Matrix m, Vector v);
Matrix generate_first_matrix(int size);
Matrix generate_second_matrix(int size);
BandedMatrix generate_third_matrix(int size, double k, double m);
Vector generate_example_vector(int length);
Vector multiply_banded_matrix_by_vector(BandedMatrix m, Vector v);
Vector thomas(BandedMatrix matrix);

#endif //LAB2_EXCERCISE_DOUBLE_H
