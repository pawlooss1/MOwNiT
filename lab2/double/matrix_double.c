//
// Created by pawel on 20.03.19.
//

#include "matrix_double.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Matrix allocate_matrix(int nrows, int ncols) {
    double **arr = (double **) malloc(nrows * sizeof(double *));
    for (int i = 0; i < nrows; i++)
        arr[i] = (double *) malloc(ncols * sizeof(double));

    Matrix m = {nrows, ncols, arr};
    return m;
}

void print_matrix(Matrix m) {
    int nrows = m.nrows;
    int ncols = m.ncols;
    double **matrix = m.matrix;
    for (int row = 0; row < nrows; row++) {
        printf("| ");
        for (int col = 0; col < ncols; col++) {
            printf("%f\t", matrix[row][col]);
        }
        printf("|\n");
    }
}

Matrix identity_matrix(int size) {
    double **matrix = (double **) malloc(size * sizeof(double *));
    for (int i = 0; i < size; i++)
        matrix[i] = (double *) malloc(size * sizeof(double));
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (row == col)
                matrix[row][col] = 1;
            else
                matrix[row][col] = 0;
        }
    }
    Matrix identity = {size, size, matrix};
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