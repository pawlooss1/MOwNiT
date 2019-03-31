//
// Created by pawel on 20.03.19.
//

#ifndef LAB2_EXCERCISE_DOUBLE_H
#define LAB2_EXCERCISE_DOUBLE_H

#include "vector_double.h"
#include "matrix_double.h"
#include "banded_matrix_double.h"

Matrix *create_augmented_matrix(Matrix *m, Vector *v);

Vector *multiply_matrix_by_vector(Matrix *m, Vector *v);

Vector *generate_example_vector(int length);

Vector *generate_iteration_vector(int length, double value);

Matrix *generate_exercise_matrix(int size);

Vector *multiply_banded_matrix_by_vector(BandedMatrix m, Vector *v);

Vector *jacobi_first_criterion(Matrix *a, Vector *b, Vector *x, double threshold);

Vector *jacobi_second_criterion(Matrix *a, Vector *b, Vector *x, double threshold);

Vector *sor(Matrix *a, Vector *b, Vector *x, double threshold, double omega);

double jacobi_spectral_radius_check(Matrix *A);

Matrix *extract_inverted_diagonal(Matrix *a);

double find_max_eigenvalue(Matrix *m);

Vector *power_iteration(Matrix *m, double epsilon);

#endif //LAB2_EXCERCISE_DOUBLE_H
