#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct Matrix {
    int nrows;
    int ncols;
    double **matrix;
} Matrix;

typedef struct Vector {
    int length;
    double *vector;
} Vector;

Matrix allocate_matrix(int nrows, int ncols) {
    double **arr = (double **) malloc(nrows * sizeof(double *));
    for (int i = 0; i < nrows; i++)
        arr[i] = (double *) malloc(ncols * sizeof(double));

    Matrix m = {nrows, ncols, arr};
    return m;
}

Vector allocate_vector(int length) {
    double *vec = (double *) malloc(length * sizeof(double_t));
    for (int i = 0; i < length; i++) {
        vec[i] = i;
    }
    Vector v = {length, vec};
    return v;
}

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

void print_vector(Vector v) {
    int length = v.length;
    double *vector = v.vector;
    for (int i = 0; i < length; i++) {
        printf("| %f |\n", vector[i]);
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
        for (int k = i - 1; i >= 0; i--)
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

double euclid_norm(Vector x, Vector x_calc) {
    double sum = 0;
    Vector v = allocate_vector(x.length);
    for (int i = 0; i < x.length; i++) {
        v.vector[i] = x.vector[i] - x_calc.vector[i];
    }
    for (int i = 0; i < v.length; i++) {
        sum += v.vector[i] * v.vector[i];
    }
    return sqrt(sum);
}

double max_norm(Vector x, Vector x_calc) {
    Vector v = allocate_vector(x.length);
    for (int i = 0; i < x.length; i++) {
        v.vector[i] = (double) (x.vector[i] - x_calc.vector[i]);
    }
    double max = fabs(v.vector[0]);
    for (int i = 1; i < v.length; i++) {
        if (fabs(v.vector[i]) > max)
            max = fabs(v.vector[i]);
    }
    return max;
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

Vector generate_example_vector(int length) {
    Vector result = allocate_vector(length);
    for (int i = 0; i < length; i++) {
        if (i % 2 == 0)
            result.vector[i] = 1.0;
        else
            result.vector[i] = -1.0;
    }
    return result;
}


typedef struct Matrix_f {
    int nrows;
    int ncols;
    float **matrix;
} Matrix_f;

typedef struct Vector_f {
    int length;
    float *vector;
} Vector_f;

Matrix_f allocate_matrix_f(int nrows, int ncols) {
    float **arr = (float **) malloc(nrows * sizeof(float *));
    for (int i = 0; i < nrows; i++)
        arr[i] = (float *) malloc(ncols * sizeof(float));

    Matrix_f m = {nrows, ncols, arr};
    return m;
}

Vector_f allocate_vector_f(int length) {
    float *vec = (float *) malloc(length * sizeof(float));
    for (int i = 0; i < length; i++) {
        vec[i] = i;
    }
    Vector_f v = {length, vec};
    return v;
}

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

void print_matrix_f(Matrix_f m) {
    int nrows = m.nrows;
    int ncols = m.ncols;
    float **matrix = m.matrix;
    for (int row = 0; row < nrows; row++) {
        printf("| ");
        for (int col = 0; col < ncols; col++) {
            printf("%f\t", matrix[row][col]);
        }
        printf("|\n");
    }
}

void print_vector_f(Vector_f v) {
    int length = v.length;
    float *vector = v.vector;
    for (int i = 0; i < length; i++) {
        printf("| %f |\n", vector[i]);
    }
}

Matrix_f identity_matrix_f(int size) {
    float **matrix = (float **) malloc(size * sizeof(float *));
    for (int i = 0; i < size; i++)
        matrix[i] = (float *) malloc(size * sizeof(float));
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (row == col)
                matrix[row][col] = 1;
            else
                matrix[row][col] = 0;
        }
    }
    Matrix_f identity = {size, size, matrix};
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
        for (int k = i - 1; i >= 0; i--)
            a.matrix[k][n] -= a.matrix[k][i] * x.vector[i];
    }
    return x;
}

float euclid_norm_f(Vector_f x, Vector_f x_calc) {
    float sum = 0;
    Vector_f v = allocate_vector_f(x.length);
    for (int i = 0; i < x.length; i++) {
        v.vector[i] = x.vector[i] - x_calc.vector[i];
    }
    for (int i = 0; i < v.length; i++) {
        sum += v.vector[i] * v.vector[i];
    }
    return sqrtf(sum);
}

float max_norm_f(Vector_f x, Vector_f x_calc) {
    Vector_f v = allocate_vector_f(x.length);
    for (int i = 0; i < x.length; i++) {
        v.vector[i] = x.vector[i] - x_calc.vector[i];
    }
    float max = fabsf(v.vector[0]);
    for (int i = 1; i < v.length; i++) {
        if (fabsf(v.vector[i]) > max) max = fabsf(v.vector[i]);
    }
    return max;
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

void zad1(int max_size) {
    printf("zad1:\nn\teukl\t\tmaks\t\teukl_f\t\tmaks_f\n");
    for (int n = 3; n <= max_size; n++) {
        Matrix A = generate_first_matrix(n);
        Vector x_zad = generate_example_vector(n);
        Vector b = multiply_matrix_by_vector(A, x_zad);
        Matrix Ax = create_augmented_matrix(A, b);
        Vector x_obl = gauss(Ax);
        double eukl = euclid_norm(x_zad, x_obl);
        double max = max_norm(x_zad, x_obl);

        Matrix_f A_f = generate_first_matrix_f(n);
        Vector_f x_zad_f = generate_example_vector_f(n);
        Vector_f b_f = multiply_matrix_by_vector_f(A_f, x_zad_f);
        Matrix_f Ax_f = create_augmented_matrix_f(A_f, b_f);
        Vector_f x_obl_f = gauss_f(Ax_f);
        float eukl_f = euclid_norm_f(x_zad_f, x_obl_f);
        float max_f = max_norm_f(x_zad_f, x_obl_f);

        printf("%d\t%f\t%f\t%f\t%f\t\n", n, eukl, max, eukl_f, max_f);
    }
    printf("\n\n");
}

void zad2(int max_size) {
    printf("zad2:\nn\teukl\t\tmaks\t\teukl_f\t\tmaks_f\n");
    for (int n = 3; n <= max_size; n++) {
        Matrix A = generate_second_matrix(n);
        Vector x_zad = generate_example_vector(n);
        Vector b = multiply_matrix_by_vector(A, x_zad);
        Matrix Ax = create_augmented_matrix(A, b);
        Vector x_obl = gauss(Ax);
        double eukl = euclid_norm(x_zad, x_obl);
        double max = max_norm(x_zad, x_obl);

        Matrix_f A_f = generate_second_matrix_f(n);
        Vector_f x_zad_f = generate_example_vector_f(n);
        Vector_f b_f = multiply_matrix_by_vector_f(A_f, x_zad_f);
        Matrix_f Ax_f = create_augmented_matrix_f(A_f, b_f);
        Vector_f x_obl_f = gauss_f(Ax_f);
        float eukl_f = euclid_norm_f(x_zad_f, x_obl_f);
        float max_f = max_norm_f(x_zad_f, x_obl_f);

        printf("%d\t%f\t%f\t%f\t%f\t\n", n, eukl, max, eukl_f, max_f);
    }
    printf("\n\n");
}

int main() {
    zad1(200);
    zad2(200);
    return 0;
}