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
    int iterations1, iterations2;

    Matrix *m = generate_exercise_matrix(size);
    Vector *x = generate_iteration_vector(size, start_vector_value);
    Vector *x_zad = generate_example_vector(size);
    Vector *b = multiply_matrix_by_vector(m, x_zad);

    start = times(&tmsstart);
    iterations1 = jacobi_first_criterion(m, b, x, threshold);
    end = times(&tmsend);
    real_time1 = (end - start) / (double) clktck;
    double eukl1 = euclid_norm(x_zad, x);
    double max1 = max_norm(x_zad, x);

    free_vector(x);
    x = generate_iteration_vector(size, start_vector_value);

    start = times(&tmsstart);
    iterations2 = jacobi_second_criterion(m, b, x, threshold);
    end = times(&tmsend);
    real_time2 = (end - start) / (double) clktck;
    double eukl2 = euclid_norm(x_zad, x);
    double max2 = max_norm(x_zad, x);

    printf("%5d\t%d\t%e\t%e\t%e\t%d\t%e\t%e\t%e\t\n", size, iterations1, eukl1, max1, real_time1, iterations2, eukl2, max2, real_time2);
}

void ex1_diff_iteration_vector(int size, double threshold) {
    struct tms tmsstart, tmsend;
    clock_t start, end;
    double real_time1, real_time2;
    long clktck = sysconf(_SC_CLK_TCK);
    int iterations1, iterations2;

    Matrix *m = generate_exercise_matrix(size);
    Vector *x = generate_iteration_vector_diff_val(size);
    Vector *x_zad = generate_example_vector(size);
    Vector *b = multiply_matrix_by_vector(m, x_zad);

    start = times(&tmsstart);
    iterations1 = jacobi_first_criterion(m, b, x, threshold);
    end = times(&tmsend);
    real_time1 = (end - start) / (double) clktck;
    double eukl1 = euclid_norm(x_zad, x);
    double max1 = max_norm(x_zad, x);

    free_vector(x);
    x = generate_iteration_vector_diff_val(size);

    start = times(&tmsstart);
    iterations2 = jacobi_second_criterion(m, b, x, threshold);
    end = times(&tmsend);
    real_time2 = (end - start) / (double) clktck;
    double eukl2 = euclid_norm(x_zad, x);
    double max2 = max_norm(x_zad, x);

    printf("%5d\t%d\t%e\t%e\t%e\t%d\t%e\t%e\t%e\t\n", size, iterations1, eukl1, max1, real_time1, iterations2, eukl2, max2, real_time2);
}

void ex2(int size, double start_vector_value, double threshold, double omega) {
    struct tms tmsstart, tmsend;
    clock_t start, end;
    double real_time1;
    long clktck = sysconf(_SC_CLK_TCK);
    int iterations = 0;

    Matrix *m = generate_exercise_matrix(size);
    Vector *x = generate_iteration_vector(size, start_vector_value);
    Vector *x_zad = generate_example_vector(size);
    Vector *b = multiply_matrix_by_vector(m, x_zad);

    start = times(&tmsstart);
    iterations = sor(m, b, x, threshold, omega);
    end = times(&tmsend);
    real_time1 = (end - start) / (double) clktck;
    double eukl1 = euclid_norm(x_zad, x);
    double max1 = max_norm(x_zad, x);

    free_vector(x);

    printf("%5d\t%e\t%e\t%d\t%e\n", size, eukl1, max1, iterations, real_time1);
}

int main() {
    double start_value = 0.0;
    double ro = 0.0001;
    double omega;
    printf("zad1 (wartosci wektora poczatkowego = %f, ro = %e):\n", start_value, ro);
    printf("n\t\tit1\teukl1\t\t\tmaks1\t\t\ttime1\t\t\tit2\teukl2\t\t\tmaks2\t\t\ttime2\n");
    ex1(5, start_value, ro);
    ex1(25, start_value, ro);
    ex1(50, start_value, ro);
    ex1(100, start_value, ro);
    ex1(250, start_value, ro);
    ex1(1000, start_value, ro);
    ex1(3000, start_value, ro);

    start_value = 100;
    printf("\nzad1 (wartosci wektora poczatkowego = %f, ro = %e):\n", start_value, ro);
    printf("n\t\tit1\teukl1\t\t\tmaks1\t\t\ttime1\t\t\tit2\teukl2\t\t\tmaks2\t\t\ttime2\n");
    ex1(5, start_value, ro);
    ex1(50, start_value, ro);
    ex1(250, start_value, ro);
    ex1(1000, start_value, ro);

    printf("\nzad1 (wartosci wektora poczatkowego = różne, ro = %e):\n", ro);
    printf("n\t\tit1\teukl1\t\t\tmaks1\t\t\ttime1\t\t\tit2\teukl2\t\t\tmaks2\t\t\ttime2\n");
    ex1_diff_iteration_vector(5, ro);
    ex1_diff_iteration_vector(50, ro);
    ex1_diff_iteration_vector(250, ro);
    ex1_diff_iteration_vector(1000, ro);

    start_value = 0;
    ro = 0.00001;
    printf("\nzad1 (wartosci wektora poczatkowego = %f, ro = %e):\n", start_value, ro);
    printf("n\t\tit1\teukl1\t\t\tmaks1\t\t\ttime1\t\t\tit2\teukl2\t\t\tmaks2\t\t\ttime2\n");
    ex1(100, start_value, ro);
    ex1(1000, start_value, ro);

    ro = 0.000001;
    printf("\nzad1 (wartosci wektora poczatkowego = %f, ro = %e):\n", start_value, ro);
    printf("n\t\tit1\teukl1\t\t\tmaks1\t\t\ttime1\t\t\tit2\teukl2\t\t\tmaks2\t\t\ttime2\n");
    ex1(100, start_value, ro);
    ex1(1000, start_value, ro);

    ro = 0.0000001;
    printf("\nzad1 (wartosci wektora poczatkowego = %f, ro = %e):\n", start_value, ro);
    printf("n\t\tit1\teukl1\t\t\tmaks1\t\t\ttime1\t\t\tit2\teukl2\t\t\tmaks2\t\t\ttime2\n");
    ex1(100, start_value, ro);
    ex1(1000, start_value, ro);

    printf("\nPromień spektralny w metodzie jacobiego dla n = 5:\n%f\n", jacobi_spectral_radius_check(generate_exercise_matrix(5)));
    printf("Promień spektralny w metodzie jacobiego dla n = 50:\n%f\n", jacobi_spectral_radius_check(generate_exercise_matrix(50)));
    printf("Promień spektralny w metodzie jacobiego dla n = 250:\n%f\n", jacobi_spectral_radius_check(generate_exercise_matrix(250)));
    printf("Promień spektralny w metodzie jacobiego dla n = 1000:\n%f\n", jacobi_spectral_radius_check(generate_exercise_matrix(1000)));
    printf("Promień spektralny w metodzie jacobiego dla n = 2000:\n%f\n", jacobi_spectral_radius_check(generate_exercise_matrix(2000)));
    printf("Promień spektralny w metodzie jacobiego dla n = 3000:\n%f\n", jacobi_spectral_radius_check(generate_exercise_matrix(3000)));

    omega = 1;
    printf("\nzad2 (wartosci wektora poczatkowego = %f, ro = %e, omega = %.1f):\n", start_value, ro, omega);
    printf("n\t\teukl\t\t\tmaks\t\t\tit\ttime\n");
    ex2(5, start_value, ro, omega);
    ex2(25, start_value, ro, omega);
    ex2(50, start_value, ro, omega);
    ex2(100, start_value, ro, omega);
    ex2(250, start_value, ro, omega);
    ex2(1000, start_value, ro, omega);
    ex2(3000, start_value, ro, omega);

    omega = 1;
    printf("\nzad2 (wartosci wektora poczatkowego = %f, ro = %e, omega = %.1f):\n", start_value, ro, omega);
    printf("n\t\teukl\t\t\tmaks\t\t\tit\ttime\n");
    ex2(100, start_value, ro, omega);
    ex2(1000, start_value, ro, omega);

    omega = 1.1;
    printf("\nzad2 (wartosci wektora poczatkowego = %f, ro = %e, omega = %.1f):\n", start_value, ro, omega);
    printf("n\t\teukl\t\t\tmaks\t\t\tit\ttime\n");
    ex2(100, start_value, ro, omega);
    ex2(1000, start_value, ro, omega);

    omega = 1.5;
    printf("\nzad2 (wartosci wektora poczatkowego = %f, ro = %e, omega = %.1f):\n", start_value, ro, omega);
    printf("n\t\teukl\t\t\tmaks\t\t\tit\ttime\n");
    ex2(100, start_value, ro, omega);
    ex2(1000, start_value, ro, omega);

    omega = 0.9;
    printf("\nzad2 (wartosci wektora poczatkowego = %f, ro = %e, omega = %.1f):\n", start_value, ro, omega);
    printf("n\t\teukl\t\t\tmaks\t\t\tit\ttime\n");
    ex2(100, start_value, ro, omega);
    ex2(1000, start_value, ro, omega);

    omega = 0.5;
    printf("\nzad2 (wartosci wektora poczatkowego = %f, ro = %e, omega = %.1f):\n", start_value, ro, omega);
    printf("n\t\teukl\t\t\tmaks\t\t\tit\ttime\n");
    ex2(100, start_value, ro, omega);
    ex2(1000, start_value, ro, omega);

    return 0;
}