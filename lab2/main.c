#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>
#include <zconf.h>
#include "double/excercise_double.h"
#include "float/exercise_float.h"
#include "float/banded_matrix_float.h"


void ex1(int size) {
    Matrix A = generate_first_matrix(size);
    Vector x_zad = generate_example_vector(size);
    Vector b = multiply_matrix_by_vector(A, x_zad);
    Matrix Ax = create_augmented_matrix(A, b);
    Vector x_obl = gauss(Ax);
    double eukl = euclid_norm(x_zad, x_obl);
    double max = max_norm(x_zad, x_obl);

    Matrix_f A_f = generate_first_matrix_f(size);
    Vector_f x_zad_f = generate_example_vector_f(size);
    Vector_f b_f = multiply_matrix_by_vector_f(A_f, x_zad_f);
    Matrix_f Ax_f = create_augmented_matrix_f(A_f, b_f);
    Vector_f x_obl_f = gauss_f(Ax_f);
    float eukl_f = euclid_norm_f(x_zad_f, x_obl_f);
    float max_f = max_norm_f(x_zad_f, x_obl_f);

    printf("%d\t\t%f\t%f\t%f\t%f\t\n", size, eukl, max, eukl_f, max_f);
}

void ex2(int size) {
    Matrix A = generate_second_matrix(size);
    Vector x_zad = generate_example_vector(size);
    Vector b = multiply_matrix_by_vector(A, x_zad);
    Matrix Ax = create_augmented_matrix(A, b);
    Vector x_obl = gauss(Ax);
    double eukl = euclid_norm(x_zad, x_obl);
    double max = max_norm(x_zad, x_obl);

    Matrix_f A_f = generate_second_matrix_f(size);
    Vector_f x_zad_f = generate_example_vector_f(size);
    Vector_f b_f = multiply_matrix_by_vector_f(A_f, x_zad_f);
    Matrix_f Ax_f = create_augmented_matrix_f(A_f, b_f);
    Vector_f x_obl_f = gauss_f(Ax_f);
    float eukl_f = euclid_norm_f(x_zad_f, x_obl_f);
    float max_f = max_norm_f(x_zad_f, x_obl_f);

    printf("%4d\t%e\t%e\t%f\t%f\t\n", size, eukl, max, eukl_f, max_f);
}

void ex3_thomas(int size) {
    struct tms tmsstart, tmsend;
    clock_t start, end;
    double real_time, real_time_f;
    long clktck = sysconf(_SC_CLK_TCK);

    BandedMatrix *A = generate_third_matrix_banded(size, 6.0, 3.0);
    Vector x_zad = generate_example_vector(size);
    Vector b = multiply_banded_matrix_by_vector(A, x_zad);
    A->right_column = b.vector;
    start = times(&tmsstart);
    Vector x_obl = thomas(A);
    end = times(&tmsend);
    real_time = (end - start) / (double) clktck;
    double eukl = euclid_norm(x_zad, x_obl);
    double max = max_norm(x_zad, x_obl);

    BandedMatrix_f A_f = generate_third_matrix_banded_f(size, 6.0, 3.0);
    Vector_f x_zad_f = generate_example_vector_f(size);
    Vector_f b_f = multiply_banded_matrix_by_vector_f(A_f, x_zad_f);
    A_f.right_column = b_f.vector;
    start = times(&tmsstart);
    Vector_f x_obl_f = thomas_f(A_f);
    end = times(&tmsend);
    real_time_f = (end - start) / (double) clktck;
    float eukl_f = euclid_norm_f(x_zad_f, x_obl_f);
    float max_f = max_norm_f(x_zad_f, x_obl_f);

    printf("%4d\t%e\t%e\t%e\t%e\t%e\n", size, eukl, max, eukl_f, max_f, real_time);
}

void ex3_gauss(int size) {
    struct tms tmsstart, tmsend;
    clock_t start, end;
    double real_time, real_time_f;
    long clktck = sysconf(_SC_CLK_TCK);

    Matrix A = generate_third_matrix_classic(size, 6.0, 3.0);
    Vector x_zad = generate_example_vector(size);
    Vector b = multiply_matrix_by_vector(A, x_zad);
    Matrix Ax = create_augmented_matrix(A, b);
    start = times(&tmsstart);
    Vector x_obl = gauss(Ax);
    end = times(&tmsend);
    real_time = (end - start) / (double) clktck;
    double eukl = euclid_norm(x_zad, x_obl);
    double max = max_norm(x_zad, x_obl);

    Matrix_f A_f = generate_third_matrix_classic_f(size, 6.0, 3.0);
    Vector_f x_zad_f = generate_example_vector_f(size);
    Vector_f b_f = multiply_matrix_by_vector_f(A_f, x_zad_f);
    Matrix_f Ax_f = create_augmented_matrix_f(A_f, b_f);
    start = times(&tmsstart);
    Vector_f x_obl_f = gauss_f(Ax_f);
    end = times(&tmsend);
    real_time_f = (end - start) / (double) clktck;
    float eukl_f = euclid_norm_f(x_zad_f, x_obl_f);
    float max_f = max_norm_f(x_zad_f, x_obl_f);

    printf("%4d\t%e\t%e\t%e\t%e\t%e\n", size, eukl, max, eukl_f, max_f, real_time);
}

int main() {
    printf("zad1:\nn\t\teukl\t\tmaks\t\teukl_f\t\tmaks_f\n");
    for (int i = 4; i <= 20; i += 2)
        ex1(i);

    printf("\nzad2:\nn\t\teukl\t\t\tmaks\t\t\teukl_f\t\tmaks_f\n");
    ex2(5);
    ex2(10);
    ex2(25);
    ex2(50);
    ex2(100);
    ex2(500);
    //ex2(1000);
    //ex2(2500);

    printf("\nzad3(Thomas):\nn\t\teukl\t\t\tmaks\t\t\teukl_f\t\t\tmaks_f\t\t\ttime\n");
    ex3_thomas(5);
    ex3_thomas(10);
    ex3_thomas(25);
    ex3_thomas(100);
    ex3_thomas(500);
    ex3_thomas(1500);
    ex3_thomas(5000);
    ex3_thomas(500000);

    printf("\nzad3(Gauss):\nn\t\teukl\t\t\tmaks\t\t\teukl_f\t\t\tmaks_f\t\t\ttime\n");
    ex3_gauss(5);
    ex3_gauss(10);
    ex3_gauss(25);
    ex3_gauss(100);
    ex3_gauss(500);
    ex3_gauss(1500);
}