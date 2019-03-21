//
// Created by pawel on 20.03.19.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vector_float.h"

Vector_f *allocate_vector_f(int length) {
    float *vec = (float *) malloc(length * sizeof(float));
    Vector_f *v = malloc(sizeof(Vector_f));
    v->vector = vec;
    v->length = length;
    return v;
}

void free_vector_f(Vector_f *v) {
    free(v->vector);
    free(v);
}

Vector_f *copy_vector_f(Vector_f *v) {
    Vector_f *result = allocate_vector_f(v->length);
    for (int i = 0; i < v->length; i++)
        result->vector[i] = v->vector[i];
    return result;
}

void print_vector_f(Vector_f *v) {
    int length = v->length;
    float *vector = v->vector;
    for (int i = 0; i < length; i++) {
        printf("| %f |\n", vector[i]);
    }
    printf("\n");
}

float euclid_norm_f(Vector_f *x, Vector_f *x_calc) {
    float sum = 0;
    Vector_f *v = allocate_vector_f(x->length);
    for (int i = 0; i < x->length; i++) {
        v->vector[i] = x->vector[i] - x_calc->vector[i];
    }
    for (int i = 0; i < v->length; i++) {
        sum += v->vector[i] * v->vector[i];
    }
    free_vector_f(v);
    return sqrtf(sum);
}

float max_norm_f(Vector_f *x, Vector_f *x_calc) {
    Vector_f *v = allocate_vector_f(x->length);
    for (int i = 0; i < x->length; i++) {
        v->vector[i] = x->vector[i] - x_calc->vector[i];
    }
    float max = fabsf(v->vector[0]);
    for (int i = 1; i < v->length; i++) {
        if (fabsf(v->vector[i]) > max) max = fabsf(v->vector[i]);
    }
    free_vector_f(v);
    return max;
}

