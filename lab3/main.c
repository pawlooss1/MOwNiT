#include <stdio.h>
#include "double/matrix_double.h"
#include "double/vector_double.h"
#include "double/excercise_double.h"

int main() {
    double r1[] = {1.0, 1.0/2, 1.0/3};
    double r2[] = {1.0/3, 1.0, 1.0/2};
    double r3[] = {1.0/2, 1.0/3, 1.0};
    double* m[] = {r1, r2, r3};
    Matrix a = {3, 3, m};

    double v[] = {0.0, 0.0, 0.0};
    double v2[] = {11.0/18, 11.0/18., 11.0/18};
    Vector x = {3, v};
    Vector b = {3, v2};

    jacobi(&a, &b, &x, 10);

    return 0;
}