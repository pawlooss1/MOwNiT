//
// Created by pawel on 20.03.19.
//

#include <stdlib.h>
#include <stdio.h>
#include "matrix_float.h"

Matrix_f *allocate_matrix_f(int nrows, int ncols) {
    float **arr = (float **) malloc(nrows * sizeof(float *));
    for (int i = 0; i < nrows; i++)
        arr[i] = (float *) malloc(ncols * sizeof(float));

    Matrix_f *m = malloc(sizeof(Matrix_f));
    m->matrix = arr;
    m->nrows = nrows;
    m->ncols = ncols;
    return m;
}

void free_matrix_f(Matrix_f *m) {
    for (int i = 0; i < m->nrows; i++)
        free(m->matrix[i]);
    free(m->matrix);
    free(m);
}

void print_matrix_f(Matrix_f *m) {
    int nrows = m->nrows;
    int ncols = m->ncols;
    float **matrix = m->matrix;
    for (int row = 0; row < nrows; row++) {
        printf("| ");
        for (int col = 0; col < ncols; col++) {
            printf("%f\t", matrix[row][col]);
        }
        printf("|\n");
    }
}

Matrix_f *identity_matrix_f(int size) {
    Matrix_f *identity = allocate_matrix_f(size, size);
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

void swap_rows_f(float **row1, float **row2) {  // w wywolaniu nalezy dac & przed wierszem
    float *tmp = *row1;
    *row1 = *row2;
    *row2 = tmp;
}

void add_rows_f(float *row1, float *row2, int ncols) {
    for (int i = 0; i < ncols; i++) {
        row1[i] = row1[i] + row2[i];
    }
}

void multiply_row_by_const_f(float *row, float constant, int ncols) {
    for (int i = 0; i < ncols; i++) {
        row[i] = row[i] * constant;
    }
}

