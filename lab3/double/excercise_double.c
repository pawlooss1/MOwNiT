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

Vector *generate_iteration_vector(int length, double value) {
    Vector *result = allocate_vector(length);
    for (int i = 0; i < length; i++) {
        result->vector[i] = value;
    }
    return result;
}

Vector *generate_iteration_vector_diff_val(int length) {
    Vector *result = allocate_vector(length);
    for (int i = 0; i < length; i++) {
        result->vector[i] = (i * i * i) % 200 - 100;
    }
    return result;
}

Matrix *generate_exercise_matrix(int size) {
    Matrix *result = allocate_matrix(size, size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (row == col)
                result->matrix[row][col] = 10;  //parametr k = 10
            else
                result->matrix[row][col] = 1 / (double) (abs(row - col) + 5);
        }
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

int jacobi_first_criterion(Matrix *a, Vector *b, Vector *x, double threshold) {
    Vector *u = copy_vector(x);
    double criterion, sum, diag;
    int n = x->length;
    int iterations = 0;
    do {
        copy_vector_values(x, u);
        for (int i = 0; i < n; i++) {
            sum = b->vector[i];
            diag = a->matrix[i][i];
            for (int j = 0; j < n; j++) {
                if (j != i)
                    sum -= (a->matrix[i][j] * u->vector[j]);
            }
            x->vector[i] = sum / diag;
        }
        criterion = euclid_norm(x, u);
        iterations++;
    } while (criterion > threshold);
    free_vector(u);
    return iterations;
}

int jacobi_second_criterion(Matrix *a, Vector *b, Vector *x, double threshold) {
    Vector *u = copy_vector(x);
    double criterion, sum, diag;
    int n = x->length;
    int iterations = 0;
    do {
        copy_vector_values(x, u);
        for (int i = 0; i < n; i++) {
            sum = b->vector[i];
            diag = a->matrix[i][i];
            for (int j = 0; j < n; j++) {
                if (j != i)
                    sum -= (a->matrix[i][j] * u->vector[j]);
            }
            x->vector[i] = sum / diag;
        }
        criterion = euclid_norm(multiply_matrix_by_vector(a, x), b);
        iterations++;
    } while (criterion > threshold);
    free_vector(u);
    return iterations;
}

int sor(Matrix *a, Vector *b, Vector *x, double threshold, double omega) {
    Vector *u = copy_vector(x);
    double criterion, sum, diag;
    int n = x->length;
    int iterations = 0;
    do {
        copy_vector_values(x, u);
        for (int i = 0; i < n; i++) {
            sum = b->vector[i];
            diag = a->matrix[i][i];
            for (int j = 0; j < i; j++)
                sum -= a->matrix[i][j] * x->vector[j];
            for (int j = i + 1; j < n; j++)
                sum -= a->matrix[i][j] * x->vector[j];
            x->vector[i] = sum / diag;
            x->vector[i] = omega * x->vector[i] + (1 - omega) * u->vector[i];
        }
        criterion = euclid_norm(x, u);
        iterations++;
    } while (criterion > threshold);
    return iterations;
}

double jacobi_spectral_radius_check(Matrix *A) {
    Matrix *Q_1 = extract_inverted_diagonal(A);
    Matrix *Q_1A = matrix_multiplication(Q_1, A);
    Matrix *B = matrix_substraction(identity_matrix(A->ncols), Q_1A);
    double result = find_max_eigenvalue(B);
    free_matrix(Q_1);
    free_matrix(Q_1A);
    free_matrix(B);
    return result;
}

Matrix *extract_inverted_diagonal(Matrix *a) {
    Matrix *result = allocate_matrix(a->nrows, a->ncols);
    for (int row = 0; row < a->nrows; row++) {
        for (int col = 0; col < a->ncols; col++) {
            if (row == col)
                result->matrix[row][col] = 1 / a->matrix[row][col];
            else
                result->matrix[row][col] = 0;
        }
    }
    return result;
}

double find_max_eigenvalue(Matrix *m) {
    Vector *max_eigenvector = power_iteration(m, 0.001);
    Vector *Mx = multiply_matrix_by_vector(m, max_eigenvector);
    double xTMx = dot_product(max_eigenvector, Mx);
    double xTx = dot_product(max_eigenvector, max_eigenvector);
    double result = xTMx / xTx;
    free_vector(max_eigenvector);
    free_vector(Mx);
    return fabs(result);
}

Vector *power_iteration(Matrix *m, double epsilon) {
    Vector *b_k = allocate_vector(m->nrows);
    Vector *b_k1 = generate_random_vector(m->nrows);
    int max_iterations = 1000;
    int i = 0;
    double b_k1_norm;
    do {
        copy_vector_values(b_k1, b_k);
        free_vector(b_k1);
        b_k1 = multiply_matrix_by_vector(m, b_k);
        b_k1_norm = norm(b_k1);
        multiply_vector_by_const(b_k1, 1 / b_k1_norm);
        i++;
    } while (max_norm(b_k, b_k1) > epsilon && i < max_iterations);
    free_vector(b_k);
    return b_k1;
}