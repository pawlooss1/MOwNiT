//
// Created by pawel on 20.03.19.
//

#ifndef LAB2_MATRIX_DOUBLE_H
#define LAB2_MATRIX_DOUBLE_H

typedef struct Matrix {
    int nrows;
    int ncols;
    double **matrix;
} Matrix;

Matrix allocate_matrix(int nrows, int ncols);
void print_matrix(Matrix m);
Matrix identity_matrix(int size);
void swap_rows(double **row1, double **row2);
void add_rows(double *row1, double *row2, int ncols);
void multiply_row_by_const(double *row, double constant, int ncols);

#endif //LAB2_MATRIX_DOUBLE_H
