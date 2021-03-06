//
// Created by pawel on 20.03.19.
//

#include "vector_double.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Vector allocate_vector(int length) {
    double *vec = (double *) malloc(length * sizeof(double_t));
    for (int i = 0; i < length; i++) {
        vec[i] = i;
    }
    Vector v = {length, vec};
    return v;
}

void print_vector(Vector v) {
    int length = v.length;
    double *vector = v.vector;
    for (int i = 0; i < length; i++) {
        printf("| %f |\n", vector[i]);
    }
    printf("\n");
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