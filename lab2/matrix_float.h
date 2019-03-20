//
// Created by pawel on 20.03.19.
//

#ifndef LAB2_MATRIX_FLOAT_H
#define LAB2_MATRIX_FLOAT_H

typedef struct Matrix_f {
    int nrows;
    int ncols;
    float **matrix;
} Matrix_f;

Matrix_f allocate_matrix_f(int nrows, int ncols);
void print_matrix_f(Matrix_f m);
Matrix_f identity_matrix_f(int size);
void swap_rows_f(float **row1, float **row2);
void add_rows_f(float *row1, float *row2, int ncols);
void multiply_row_by_const_f(float *row, float constant, int ncols);

#endif //LAB2_MATRIX_FLOAT_H
