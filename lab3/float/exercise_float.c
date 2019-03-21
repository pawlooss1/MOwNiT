//
// Created by pawel on 20.03.19.
//

#include "exercise_float.h"
#include "matrix_float.h"
#include "vector_float.h"
#include "banded_matrix_float.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Matrix_f *create_augmented_matrix_f(Matrix_f *m, Vector_f *v) {
    if (m->nrows != v->length) {
        return NULL;
    }
    Matrix_f *result = allocate_matrix_f(m->nrows, m->ncols + 1);
    for (int row = 0; row < m->nrows; row++) {
        for (int col = 0; col < m->ncols; col++)
            result->matrix[row][col] = m->matrix[row][col];
    }
    for (int row = 0; row < v->length; row++)
        result->matrix[row][result->ncols - 1] = v->vector[row];
    return result;
}

Vector_f *multiply_matrix_by_vector_f(Matrix_f *m, Vector_f *v) {
    Vector_f *result = allocate_vector_f(v->length);
    for (int i = 0; i < v->length; i++) {
        result->vector[i] = 0.0;
        for (int j = 0; j < v->length; j++) {
            result->vector[i] += v->vector[j] * m->matrix[i][j];
        }
    }
    return result;
}

Vector_f *generate_example_vector_f(int length) {
    Vector_f *result = allocate_vector_f(length);
    for (int i = 0; i < length; i++) {
        if (i % 2 == 0)
            result->vector[i] = -1;
        else
            result->vector[i] = 1;
    }
    return result;
}

Vector_f *multiply_banded_matrix_by_vector_f(BandedMatrix_f m, Vector_f *v) {
    int n = v->length;
    Vector_f *result = allocate_vector_f(n);
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

Vector_f *jacobi_f(Matrix_f *a, Vector_f *b, Vector_f *x, int number_of_iterations) {
    Vector_f *u = allocate_vector_f(x->length);
    int n = x->length;
    for (int i = 0; i < n; i++) {
        float d = 1 / a->matrix[i][i];
        b->vector[i] *= d;
        for (int j = 0; j < n; j++) {
            a->matrix[i][j] *= d;
        }
    }
    for (int k = 0; k < number_of_iterations; k++) {
        for (int i = 0; i < n; i++) {
            float sum = 0;
            for (int j = 0; j < n; j++) {
                sum += (a->matrix[i][j] * x->vector[j]);
            }
            u->vector[i] = b->vector[i] - sum;
        }
    }
    return u;
}