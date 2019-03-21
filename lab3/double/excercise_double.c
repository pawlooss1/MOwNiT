//
// Created by pawel on 20.03.19.
//

#include "excercise_double.h"
#include "vector_double.h"
#include "matrix_double.h"
#include "banded_matrix_double.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Matrix *create_augmented_matrix(Matrix *m, Vector *v) {
    if (m->nrows != v->length) {
        return NULL;
    }
    Matrix *result = allocate_matrix(m->nrows, m->ncols + 1);
    for (int row = 0; row < m->nrows; row++) {
        for (int col = 0; col < m->ncols; col++)
            result->matrix[row][col] = m->matrix[row][col];
    }
    for (int row = 0; row < v->length; row++)
        result->matrix[row][result->ncols - 1] = v->vector[row];
    return result;
}

Vector *multiply_matrix_by_vector(Matrix *m, Vector *v) {
    Vector *result = allocate_vector(v->length);
    for (int i = 0; i < v->length; i++) {
        result->vector[i] = 0.0;
        for (int j = 0; j < v->length; j++) {
            result->vector[i] += v->vector[j] * m->matrix[i][j];
        }
    }
    return result;
}

Vector *generate_example_vector(int length) {
    Vector *result = allocate_vector(length);
    for (int i = 0; i < length; i++) {
        if (i % 2 == 0)
            result->vector[i] = -1.0;
        else
            result->vector[i] = 1.0;
    }
    return result;
}

Vector *multiply_banded_matrix_by_vector(BandedMatrix m, Vector *v) {
    int n = v->length;
    Vector *result = allocate_vector(n);
    result->vector[0] = m.diagonal[0] * v->vector[0] +
                        m.upper_diagonal[0] * v->vector[1];
    for (int i = 1; i < n - 1; i++) {
        result->vector[i] = m.lower_diagonal[i] * v->vector[i - 1] +
                            m.diagonal[i] * v->vector[i] +
                            m.upper_diagonal[i] * v->vector[i + 1];
    }
    result->vector[n - 1] = m.lower_diagonal[n - 1] * v->vector[n - 2] +
                            m.diagonal[n - 1] * v->vector[n - 1];
    return result;
}

Vector *jacobi(Matrix *a, Vector *b, Vector *x, int number_of_iterations) {
    Vector *u = copy_vector(x);
    int n = x->length;
    for (int i = 0; i < n; i++) {
        double d = 1 / a->matrix[i][i];
        b->vector[i] *= d;
        for (int j = 0; j < n; j++) {
            a->matrix[i][j] *= d;
        }
    }
    for (int k = 0; k < number_of_iterations; k++) {
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int j = 0; j < n; j++) {
                if (j != i)
                    sum += (a->matrix[i][j] * u->vector[j]);
            }
            u->vector[i] = b->vector[i] - sum;
        }
        print_vector(u);
    }
    return u;
}