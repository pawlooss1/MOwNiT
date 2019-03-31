#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
#include "double/matrix_double.h"
#include "double/vector_double.h"
#include "double/excercise_double.h"

void ex1(int size, double start_vector_value, double threshold) {
    struct tms tmsstart, tmsend;
    clock_t start, end;
    double real_time1, real_time2;
    long clktck = sysconf(_SC_CLK_TCK);

    Matrix *m = generate_exercise_matrix(size);
    Vector *x = generate_iteration_vector(size, start_vector_value);
    Vector *x_zad = generate_example_vector(size);
    Vector *b = multiply_matrix_by_vector(m, x_zad);

    start = times(&tmsstart);
    Vector *result = jacobi_first_criterion(m, b, x, threshold);
    end = times(&tmsend);
    real_time1 = (end - start) / (double) clktck;
    double eukl1 = euclid_norm(x_zad, result);
    double max1 = max_norm(x_zad, result);

    free_vector(result);
    x = generate_iteration_vector(size, start_vector_value);

    start = times(&tmsstart);
    result = jacobi_second_criterion(m, b, x, threshold);
    end = times(&tmsend);
    real_time2 = (end - start) / (double) clktck;
    double eukl2 = euclid_norm(x_zad, result);
    double max2 = max_norm(x_zad, result);

    printf("%5d\t%e\t%e\t%e\t%e\t%e\t%e\t\n", size, eukl1, max1, eukl2, max2, real_time1, real_time2);
}

void ex2(int size, double start_vector_value, double threshold, double omega) {
    struct tms tmsstart, tmsend;
    clock_t start, end;
    double real_time1;
    long clktck = sysconf(_SC_CLK_TCK);

    Matrix *m = generate_exercise_matrix(size);
    Vector *x = generate_iteration_vector(size, start_vector_value);
    Vector *x_zad = generate_example_vector(size);
    Vector *b = multiply_matrix_by_vector(m, x_zad);

    start = times(&tmsstart);
    Vector *result = sor(m, b, x, threshold, omega);
    end = times(&tmsend);
    real_time1 = (end - start) / (double) clktck;
    double eukl1 = euclid_norm(x_zad, result);
    double max1 = max_norm(x_zad, result);

    free_vector(result);

    printf("%5d\t%e\t%e\t%e\n", size, eukl1, max1, real_time1);
}

int main() {
    /*double r1[] = {1.0, 1.0/2, 1.0/3};
    double r2[] = {1.0/3, 1.0, 1.0/2};
    double r3[] = {1.0/2, 1.0/3, 1.0};
    double* m[] = {r1, r2, r3};
    Matrix a = {3, 3, m};

    double v[] = {0.0, 0.0, 0.0};
    double v2[] = {11.0/18, 11.0/18., 11.0/18};
    Vector x = {3, v};
    Vector b = {3, v2};

    jacobi(&a, &b, &x, 10);*/
    double start_value = 0.0;
    double ro = 0.0001;
    double omega;
    printf("zad1 (wartosci wektora poczatkowego = %f, ro = %e):\n", start_value, ro);
    printf("n\t\teukl1\t\t\tmaks1\t\t\teukl2\t\t\tmaks2\t\t\ttime1\t\t\ttime2\n");
    ex1(5, start_value, ro);
    ex1(25, start_value, ro);
    ex1(50, start_value, ro);
    ex1(100, start_value, ro);
    ex1(250, start_value, ro);
    ex1(1000, start_value, ro);
    ex1(3000, start_value, ro);

    start_value = 1;
    printf("\nzad1 (wartosci wektora poczatkowego = %f, ro = %e):\n", start_value, ro);
    printf("n\t\teukl1\t\t\tmaks1\t\t\teukl2\t\t\tmaks2\t\t\ttime1\t\t\ttime2\n");
    ex1(5, start_value, ro);
    ex1(50, start_value, ro);
    ex1(250, start_value, ro);
    ex1(1000, start_value, ro);

    start_value = 100;
    printf("\nzad1 (wartosci wektora poczatkowego = %f, ro = %e):\n", start_value, ro);
    printf("n\t\teukl1\t\t\tmaks1\t\t\teukl2\t\t\tmaks2\t\t\ttime1\t\t\ttime2\n");
    ex1(5, start_value, ro);
    ex1(50, start_value, ro);
    ex1(250, start_value, ro);
    ex1(1000, start_value, ro);

    start_value = 0;
    ro = 0.00001;
    printf("\nzad1 (wartosci wektora poczatkowego = %f, ro = %e):\n", start_value, ro);
    printf("n\t\teukl1\t\t\tmaks1\t\t\teukl2\t\t\tmaks2\t\t\ttime1\t\t\ttime2\n");
    ex1(100, start_value, ro);
    ex1(1000, start_value, ro);

    ro = 0.000001;
    printf("\nzad1 (wartosci wektora poczatkowego = %f, ro = %e):\n", start_value, ro);
    printf("n\t\teukl1\t\t\tmaks1\t\t\teukl2\t\t\tmaks2\t\t\ttime1\t\t\ttime2\n");
    ex1(100, start_value, ro);
    ex1(1000, start_value, ro);

    ro = 0.0000001;
    printf("\nzad1 (wartosci wektora poczatkowego = %f, ro = %e):\n", start_value, ro);
    printf("n\t\teukl1\t\t\tmaks1\t\t\teukl2\t\t\tmaks2\t\t\ttime1\t\t\ttime2\n");
    ex1(100, start_value, ro);
    ex1(1000, start_value, ro);

    printf("\n\n%f\n\n", jacobi_spectral_radius_check(generate_exercise_matrix(300)));

    omega = 1;
    printf("\nzad2 (wartosci wektora poczatkowego = %f, ro = %e, omega = %.1f):\n", start_value, ro, omega);
    printf("n\t\teukl\t\t\tmaks\t\t\ttime\n");
    ex2(5, start_value, ro, omega);
    ex2(50, start_value, ro, omega);
    ex2(250, start_value, ro, omega);
    ex2(1000, start_value, ro, omega);

    omega = 1.1;
    printf("\nzad2 (wartosci wektora poczatkowego = %f, ro = %e, omega = %.1f):\n", start_value, ro, omega);
    printf("n\t\teukl\t\t\tmaks\t\t\ttime\n");
    ex2(5, start_value, ro, omega);
    ex2(50, start_value, ro, omega);
    ex2(250, start_value, ro, omega);
    ex2(1000, start_value, ro, omega);

    omega = 1.5;
    printf("\nzad2 (wartosci wektora poczatkowego = %f, ro = %e, omega = %.1f):\n", start_value, ro, omega);
    printf("n\t\teukl\t\t\tmaks\t\t\ttime\n");
    ex2(5, start_value, ro, omega);
    ex2(50, start_value, ro, omega);
    ex2(250, start_value, ro, omega);
    ex2(1000, start_value, ro, omega);

    omega = 0.9;
    printf("\nzad2 (wartosci wektora poczatkowego = %f, ro = %e, omega = %.1f):\n", start_value, ro, omega);
    printf("n\t\teukl\t\t\tmaks\t\t\ttime\n");
    ex2(5, start_value, ro, omega);
    ex2(50, start_value, ro, omega);
    ex2(250, start_value, ro, omega);
    ex2(1000, start_value, ro, omega);

    omega = 0.5;
    printf("\nzad2 (wartosci wektora poczatkowego = %f, ro = %e, omega = %.1f):\n", start_value, ro, omega);
    printf("n\t\teukl\t\t\tmaks\t\t\ttime\n");
    ex2(5, start_value, ro, omega);
    ex2(50, start_value, ro, omega);
    ex2(250, start_value, ro, omega);
    ex2(1000, start_value, ro, omega);

    return 0;
}