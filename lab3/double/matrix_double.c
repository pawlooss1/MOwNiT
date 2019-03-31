//
// Created by pawel on 20.03.19.
//

#include "matrix_double.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Matrix *allocate_matrix(int nrows, int ncols) {
    double **arr = (double **) malloc(nrows * sizeof(double *));
    for (int i = 0; i < nrows; i++)
        arr[i] = (double *) malloc(ncols * sizeof(double));

    Matrix *m = malloc(sizeof(Matrix));
    m->matrix = arr;
    m->nrows = nrows;
    m->ncols = ncols;
    return m;
}

void free_matrix(Matrix *m) {
    for (int i = 0; i < m->nrows; i++)
        free(m->matrix[i]);
    free(m->matrix);
    free(m);
}

void print_matrix(Matrix *m) {
    int nrows = m->nrows;
    int ncols = m->ncols;
    double **matrix = m->matrix;
    for (int row = 0; row < nrows; row++) {
        printf("| ");
        for (int col = 0; col < ncols; col++) {
            printf("%f\t", matrix[row][col]);
        }
        printf("|\n");
    }
}

Matrix *matrix_multiplication(Matrix *a, Matrix *b) {
    Matrix *result = allocate_matrix(a->nrows, b->ncols);
    double sum = 0;
    for (int i = 0; i < a->nrows; i++) {
        for (int j = 0; j < b->ncols; j++) {
            for (int k = 0; k < a->ncols; k++)
                sum += a->matrix[i][k] * b->matrix[k][j];
            result->matrix[i][j] = sum;
            sum = 0;
        }
    }
    return result;
}

Matrix *matrix_substraction(Matrix *a, Matrix *b) {
    Matrix *result = allocate_matrix(a->nrows, b->ncols);
    for (int i = 0; i < a->nrows; i++) {
        for (int j = 0; j < a->ncols; j++)
            result->matrix[i][j] = a->matrix[i][j] - b->matrix[i][j];
    }
    return result;
}

Matrix *identity_matrix(int size) {
    Matrix *identity = allocate_matrix(size, size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (row == col)
                identity->matrix[row][col] = 1;
            else
                identity->matrix[row][col] = 0;
        }
    }
    identity->ncols = size;
    identity->nrows = size;
    return identity;
}

void swap_rows(double **row1, double **row2) {  // w wywolaniu nalezy dac & przed wierszem
    double *tmp = *row1;
    *row1 = *row2;
    *row2 = tmp;
}

void add_rows(double *row1, double *row2, int ncols) {
    for (int i = 0; i < ncols; i++) {
        row1[i] = row1[i] + row2[i];
    }
}

void multiply_row_by_const(double *row, double constant, int ncols) {
    for (int i = 0; i < ncols; i++) {
        row[i] = row[i] * constant;
    }
}