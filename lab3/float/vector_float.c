//
// Created by pawel on 20.03.19.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vector_float.h"

Vector_f allocate_vector_f(int length) {
    float *vec = (float *) malloc(length * sizeof(float));
    for (int i = 0; i < length; i++) {
        vec[i] = i;
    }
    Vector_f v = {length, vec};
    return v;
}

void print_vector_f(Vector_f v) {
    int length = v.length;
    float *vector = v.vector;
    for (int i = 0; i < length; i++) {
        printf("| %f |\n", vector[i]);
    }
    printf("\n");
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

