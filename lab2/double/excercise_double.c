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

Matrix create_augmented_matrix(Matrix m, Vector v) {
    if (m.nrows != v.length) {
        Matrix error = {0, 0, NULL};
        return error;
    }
    Matrix result = allocate_matrix(m.nrows, m.ncols + 1);
    for (int row = 0; row < m.nrows; row++) {
        for (int col = 0; col < m.ncols; col++)
            result.matrix[row][col] = m.matrix[row][col];
    }
    for (int row = 0; row < v.length; row++)
        result.matrix[row][result.ncols - 1] = v.vector[row];
    return result;
}

Vector gauss(Matrix a) {
    int n = a.nrows;
    for (int i = 0; i < n; i++) {
        // Search for maximum in this column
        double max_el = fabs(a.matrix[i][i]);
        int max_row = i;
        for (int k = i; k < n; k++) {
            if (fabs(a.matrix[k][i]) > max_el) {
                max_el = fabs(a.matrix[k][i]);
                max_row = k;
            }
        }
        // Swap maximum row with current row
        swap_rows(&a.matrix[max_row], &a.matrix[i]);
        // Make all rows below this one 0 in current column
        for (int k = i + 1; k < n; k++) {
            double c = -a.matrix[k][i] / a.matrix[i][i];
            for (int j = i; j < n + 1; j++) {
                if (i == j)
                    a.matrix[k][j] = 0;
                else
                    a.matrix[k][j] += c * a.matrix[i][j];
            }
        }
    }
    // Solve equation for an upper triangular matrix
    Vector x = allocate_vector(n);
    for (int i = n - 1; i >= 0; i--) {
        x.vector[i] = a.matrix[i][n] / a.matrix[i][i];
        for (int k = i - 1; k >= 0; k--)
            a.matrix[k][n] -= a.matrix[k][i] * x.vector[i];
    }
    return x;
}

Vector multiply_matrix_by_vector(Matrix m, Vector v) {
    Vector result = allocate_vector(v.length);
    for (int i = 0; i < v.length; i++) {
        result.vector[i] = 0.0;
        for (int j = 0; j < v.length; j++) {
            result.vector[i] += v.vector[j] * m.matrix[i][j];
        }
    }
    return result;
}

Matrix generate_first_matrix(int size) {
    Matrix result = allocate_matrix(size, size);
    for (int j = 0; j < size; j++)
        result.matrix[0][j] = 1.0;
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.matrix[i][j] = 1.0 / (i + j + 1);
        }
    }
    return result;
}

Matrix generate_second_matrix(int size) {
    Matrix result = allocate_matrix(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j >= i)
                result.matrix[i][j] = 2.0 * (i + 1) / (j + 1);
            else
                result.matrix[i][j] = result.matrix[j][i];
        }
    }
    return result;
}

BandedMatrix generate_third_matrix_banded(int size, double k, double m) {
    BandedMatrix result = allocate_banded_matrix(size);
    for (int i = 0; i < size; i++)
        result.diagonal[i] = k;
    for (int i = 0; i < size - 1; i++)
        result.upper_diagonal[i] = 1.0 / ((double) i + m);
    for (int i = 1; i < size; i++)
        result.lower_diagonal[i] = k / ((double) i + m + 1.0);
    return result;
}

Matrix generate_third_matrix_classic(int size, double k, double m) {
    Matrix result = allocate_matrix(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j == i)
                result.matrix[i][j] = k;
            else if (j == i + 1)
                result.matrix[i][j] = 1.0 / ((double) i + m);
            else if (j == i - 1)
                result.matrix[i][j] = k / ((double) i + m + 1.0);
            else
                result.matrix[i][j] = 0.0;
        }
    }
    return result;
}

Vector generate_example_vector(int length) {
    Vector result = allocate_vector(length);
    for (int i = 0; i < length; i++) {
        if (i % 2 == 0)
            result.vector[i] = -1.0;
        else
            result.vector[i] = 1.0;
    }
    return result;
}

Vector multiply_banded_matrix_by_vector(BandedMatrix m, Vector v) {
    int n = v.length;
    Vector result = allocate_vector(n);
    result.vector[0] = m.diagonal[0] * v.vector[0] +
                       m.upper_diagonal[0] * v.vector[1];
    for (int i = 1; i < n - 1; i++) {
        result.vector[i] = m.lower_diagonal[i] * v.vector[i - 1] +
                           m.diagonal[i] * v.vector[i] +
                           m.upper_diagonal[i] * v.vector[i + 1];
    }
    result.vector[n - 1] = m.lower_diagonal[n - 1] * v.vector[n - 2] +
                           m.diagonal[n - 1] * v.vector[n - 1];
    return result;
}

Vector thomas(BandedMatrix matrix) {
    int n = matrix.size;
    double *a = matrix.lower_diagonal;
    double *b = matrix.diagonal;
    double *c = matrix.upper_diagonal;
    double *d = matrix.right_column;
    double *x = malloc(n * sizeof(double));
    double *c_star = calloc((size_t) n, sizeof(double));
    double *d_star = calloc((size_t) n, sizeof(double));

    c_star[0] = c[0] / b[0];
    d_star[0] = d[0] / b[0];
    for (int i = 1; i < n; i++) {
        double m = 1.0 / (b[i] - a[i] * c_star[i - 1]);
        c_star[i] = c[i] * m;
        d_star[i] = (d[i] - a[i] * d_star[i - 1]) * m;
    }
    for (int i = n - 1; i >= 0; i--) {
        x[i] = d_star[i] - c_star[i] * d[i + 1];
    }
    Vector result = {n, x};
    return result;
}