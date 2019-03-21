#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "double/excercise_double.h"
#include "float/exercise_float.h"


void ex1(int max_size) {
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

void ex2(int max_size) {
    printf("zad2:\nn\teukl\t\tmaks\t\teukl_f\t\tmaks_f\n");
    for (int n = 3; n <= max_size; n += 50) {
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

void ex3(int size) {
    BandedMatrix A = generate_third_matrix(size, 6.0, 3.0);
    Vector x_zad = generate_example_vector(size);
    Vector b = multiply_banded_matrix_by_vector(A, x_zad);
    A.right_column = b.vector;
    Vector x_obl = thomas(A);
    double eukl = euclid_norm(x_zad, x_obl);
    double max = max_norm(x_zad, x_obl);

    //print_vector(x_zad);
    //print_vector(x_obl);

    printf("%d\t%f\t%f\t\n", size, eukl, max);
}

int main() {
    //ex1(20);
    //ex2(1000);
    for (int i = 3; i < 10000; i++)
        ex3(i);
    return 0;
}