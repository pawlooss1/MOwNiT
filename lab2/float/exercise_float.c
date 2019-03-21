//
// Created by pawel on 20.03.19.
//

#include "exercise_float.h"
#include "matrix_float.h"
#include "vector_float.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Matrix_f create_augmented_matrix_f(Matrix_f m, Vector_f v) {
    if (m.nrows != v.length) {
        Matrix_f error = {0, 0, NULL};
        return error;
    }
    Matrix_f result = allocate_matrix_f(m.nrows, m.ncols + 1);
    for (int row = 0; row < m.nrows; row++) {
        for (int col = 0; col < m.ncols; col++)
            result.matrix[row][col] = m.matrix[row][col];
    }
    for (int row = 0; row < v.length; row++)
        result.matrix[row][result.ncols - 1] = v.vector[row];
    return result;
}

Vector_f gauss_f(Matrix_f a) {
    int n = a.nrows;
    for (int i = 0; i < n; i++) {
        // Search for maximum in this column
        float max_el = fabsf(a.matrix[i][i]);
        int max_row = i;
        for (int k = i; k < n; k++) {
            if (fabsf(a.matrix[k][i]) > max_el) {
                max_el = fabsf(a.matrix[k][i]);
                max_row = k;
            }
        }
        // Swap maximum row with current row
        swap_rows_f(&a.matrix[max_row], &a.matrix[i]);
        // Make all rows below this one 0 in current column
        for (int k = i + 1; k < n; k++) {
            float c = -a.matrix[k][i] / a.matrix[i][i];
            for (int j = i; j < n + 1; j++) {
                if (i == j)
                    a.matrix[k][j] = 0;
                else
                    a.matrix[k][j] += c * a.matrix[i][j];
            }
        }
    }
    // Solve equation for an upper triangular matrix
    Vector_f x = allocate_vector_f(n);
    for (int i = n - 1; i >= 0; i--) {
        x.vector[i] = a.matrix[i][n] / a.matrix[i][i];
        for (int k = i - 1; k >= 0; k--)
            a.matrix[k][n] -= a.matrix[k][i] * x.vector[i];
    }
    return x;
}

Vector_f multiply_matrix_by_vector_f(Matrix_f m, Vector_f v) {
    Vector_f result = allocate_vector_f(v.length);
    for (int i = 0; i < v.length; i++) {
        result.vector[i] = 0.0;
        for (int j = 0; j < v.length; j++) {
            result.vector[i] += v.vector[j] * m.matrix[i][j];
        }
    }
    return result;
}

Matrix_f generate_first_matrix_f(int size) {
    Matrix_f result = allocate_matrix_f(size, size);
    for (int j = 0; j < size; j++)
        result.matrix[0][j] = 1.0;
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.matrix[i][j] = (float) (1.0 / (i + j + 1));
        }
    }
    return result;
}

Matrix_f generate_second_matrix_f(int size) {
    Matrix_f result = allocate_matrix_f(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j >= i)
                result.matrix[i][j] = (float) (2.0 * (i + 1) / (j + 1));
            else
                result.matrix[i][j] = result.matrix[j][i];
        }
    }
    return result;
}

Vector_f generate_example_vector_f(int length) {
    Vector_f result = allocate_vector_f(length);
    for (int i = 0; i < length; i++) {
        if (i % 2 == 0)
            result.vector[i] = (float) 1.0;
        else
            result.vector[i] = (float) -1.0;
    }
    return result;
}